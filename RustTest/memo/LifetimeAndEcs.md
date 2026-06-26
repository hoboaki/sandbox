# 学習ノート：Rustゲーム開発におけるメモリ管理と設計パターン

## テーマ：Lifetimes（ライフタイム）の限界と ECS（Entity Component System）による解決

### 1. 背景：ゲーム開発におけるメモリ管理の特殊性

ゲーム開発では、「オブジェクトの生成と破棄」が頻繁に、かつ動的に発生する。

- **動的なライフサイクル**: 敵がプレイヤーに倒された瞬間、そのメモリや関連リソース（モデル、エフェクト）を即座に解放する必要がある。
- **複雑な参照関係**: 「プレイヤーが持っている武器のモデル」や「シーンに登録されたエフェクト」など、オブジェクト間で複雑な参照関係（親子関係）が生じる。

---

### 2. ライフタイム（Lifetimes）による管理の課題

Rustのライフタイム（`'a`）を用いて、オブジェクト間の参照（`&T`）を管理しようとすると、ゲーム開発特有の以下の問題に直面する。

#### ① 「借用チェッカーとの戦い」の発生

オブジェクトが「親」の生存期間に強く縛られるため、設計が極めて硬直的になる。

- **問題**: オブジェクト $A$ がオブジェクト $B$ を参照している場合、$A$ が消える前に $B$ が消えてはならない。
- **結果**: プログラムが大規模化すると、どこまで参照が及んでいるかを管理するために、膨大な数のライフタイム注釈が必要になり、設計の難易度が指数関数的に上昇する。

#### ② 「イテレーション中の書き換え」問題

これが実務上で最も頻発するエラーである。

- **シナリオ**: 「全ての敵（Entity）をループで回してHPを確認し、HPが0なら削除する」という処理。
- **エラー内容**: Rustの借用規則では、「データを読み取っている最中（不変参照中）に、そのデータを削除・変更する（可変参照）」ことは禁止されている。
- **結果**: ループの中で直接 `remove()` を呼ぶと、コンパイラに拒否される。

#### ③ パフォーマンスとキャッシュ効率

オブジェクト指向的な「ポインタの連鎖（Pointer Chasing）」は、メモリ上のあちこちにデータが散らばるため、CPUキャッシュミスを多発させ、現代のハードウェアの性能を引き出しにくい。

---

### 3. 解決策：ECS（Entity Component System）への転換

上記の問題を解決するために、ゲーム開発では「オブジェクト指向（OOP）」から「データ指向設計（DOD）」に基づいた **ECS** への移行が推奨される。

#### ECSの3大要素

1.  **Entity (エンティティ)**:
    - 実体はただの**「ID（整数値）」**。
    - 「何であるか」という情報は持たず、他のデータと紐付けるための「鍵」としてのみ機能する。
2.  **Component (コンポーネント)**:
    - 属性データ（Health, Position, Modelなど）を保持する**「純粋な構造体」**。
    - エンティティに紐付けられ、メモリ上には同じ種類が連続して並べられる。
3.  **System (システム)**:
    - コンポーネントを対象に実行される**「純粋なロジック（関数）」**。
    - 例：`HealthSystem` は `Health` コンポーネントを持つ全Entityに対して処理を行う。

#### ECSを採用するメリット

- **メモリ効率**: 同種コンポーネントがメモリに連続配置されるため、CPUキャッシュが効きやすく、極めて高速。
- **柔軟性**: 「飛べる」という機能を、継承ではなく「`FlightComponent` を付ける」という形で動的に追加・削除できる。
- **安全性**: データの所有権が「ID」によって間接的に管理されるため、ライフタイムの複雑な管理から解放され、Rustの借用チェッカーとも相性が良い。

---

### 4. 実践的なアーキテクチャ：論理と視覚の分離

大規模な設計では、**「World（論理）」**と**「Scene（視覚）」**を分離することが極めて重要である。

| 役割              | 担当範囲                       | 主なコンポーネント               |
| :---------------- | :----------------------------- | :------------------------------- |
| **World (Logic)** | ゲームのルール、生存状態、統計 | `Health`, `Stats`, `Inventory`   |
| **Scene (View)**  | 描画、空間配置、エフェクト     | `Model`, `Transform`, `Particle` |

#### 削除プロセスの設計フロー（同期プロセス）

「オブジェクトが死んだ（論理）」から「モデルが消えた（視覚）」への遷移は、以下の手順で行う。

1.  **判定 (Logic Phase)**: `World` 内のシステムが、HPが0になったEntityを特定する。
2.  **予約 (Marking Phase)**: 即座に削除せず、「削除予約リスト（Pending Deletion）」にIDを格納する。
3.  **同期 (Synchronization Phase)**:
    - `World` が削除対象のIDを確定し、`Scene` に対して「このIDのモデルを削除せよ」と通知する。
4.  **実行 (Cleanup Phase)**: フレームの終わりに、まとめて `World` と `Scene` から該当データを削除する。

```rust
use std::collections::{HashMap, HashSet};

// --- 1. 基盤となる型 ---
type Entity = u32;

// --- 2. コンポーネント (Component) ---
#[derive(Debug)]
struct Health {
    hp: i32,
}

#[derive(Debug)]
struct Model {
    mesh_name: String,
}

// --- 3. World (論理管理: Obj と Health を担当) ---
struct World {
    // 存在するEntityのリスト
    entities: HashSet<Entity>,
    // EntityごとのHealthデータ
    healths: HashMap<Entity, Health>,
    // 次のEntity ID
    next_id: Entity,
    // 削除予約リスト (イテレーション中の破壊を防ぐ)
    pending_deletion: HashSet<Entity>,
}

impl World {
    fn new() -> Self {
        Self {
            entities: HashSet::new(),
            healths: HashMap::new(),
            next_id: 0,
            pending_deletion: HashSet::new(),
        }
    }

    // Objの生成
    fn spawn_obj(&mut self) -> Entity {
        let id = self.next_id;
        self.next_id += 1;
        self.entities.insert(id);
        id
    }

    fn set_health(&mut self, entity: Entity, hp: i32) {
        self.healths.insert(entity, Health { hp });
    }

    fn get_health(&self, entity: Entity) -> Option<&Health> {
        self.healths.get(&entity)
    }

    fn mark_for_deletion(&mut self, entity: Entity) {
        self.pending_deletion.insert(entity);
    }

    // 実際の削除処理 (Sceneとの同期が必要になる)
    fn process_destruction(&mut self) -> Vec<Entity> {
        let mut deleted_entities = Vec::new();
        for entity in self.pending_deletion.drain() {
            self.entities.remove(&entity);
            self.healths.remove(&entity);
            deleted_entities.push(entity);
        }
        deleted_entities
    }
}

// --- 4. Scene (視覚管理: Model を担当) ---
struct Scene {
    // EntityID をキーにして Model を管理
    // ModelはSceneの中にしか存在しない
    models: HashMap<Entity, Model>,
}

impl Scene {
    fn new() -> Self {
        Self {
            models: HashMap::new(),
        }
    }

    // Modelの登録
    fn add_model(&mut self, entity: Entity, model: Model) {
        self.models.insert(entity, model);
    }

    // Modelの登録解除
    fn remove_model(&mut(self, entity: Entity)) {
        self.models.remove(&entity);
    }

    // 描画 (Sceneのみが行える)
    fn render(&self) {
        println!("--- [Scene Render Start] ---");
        if self.models.is_empty() {
            println!("(No models to draw)");
        } else {
            for (entity, model) in &self.models {
                println!("Entity {}: Drawing [{}]", entity, model.mesh_name);
            }
        }
        println!("--- [Scene Render End] ---");
    }
}

// --- 5. 実行フロー ---
fn main() {
    let mut world = World::new();
    let mut scene = Scene::new();

    // --- 初期設定 ---
    // 1. Objの生成
    let obj1 = world.spawn_obj();
    world.set_health(obj1, 100);
    // 2. Modelの登録 (Objの生成に伴いSceneへ)
    scene.add_model(obj1, Model { mesh_name: "Hero_Model".to_string() });

    let obj2 = world.spawn_obj();
    world.set_health(obj2, 10); // HPが低い
    scene.add_model(obj2, Model { mesh_name: "Slime_Model".to_string() });

    // --- フレーム 1 ---
    println!("=== Frame 1 ===");
    scene.render();

    // --- フレーム 2 (ダメージ発生) ---
    println!("\n>>> Damage Event: Slime takes 20 damage!");
    if let Some(health) = world.get_health(obj2) {
        let current_hp = health.hp;
        // HPが0以下になった場合、削除予約
        if current_hp - 20 <= 0 {
            world.mark_for_deletion(obj2);
        }
    }

    // --- フレーム 2 (同期処理) ---
    // 1. Worldで死亡したEntityを特定し、Sceneからモデルを消す
    let dead_entities = world.process_destruction();
    for entity in dead_entities {
        println!("Logic: Entity {} is dead. Removing from Scene.", entity);
        scene.remove_model(entity);
    }

    // 2. 描画
    scene.render();
}
```

**結論:**
Rustにおいてゲームを構築する際は、「ライフタイムによる厳密な参照管理」を避け、「IDによる疎結合なデータ管理（ECS）」と「論理と視覚の分離」を採用することが、安全かつ高性能なエンジンを設計するための鍵となる。
