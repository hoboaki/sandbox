// 文字コード：UTF-8
pub struct Character {
    pub position: Vector3,
    pub name: String,
    pub hit_point: i32,
}

impl Character {
    pub fn new(name: String, position: Vector3) -> Self {
        Self::new_with_hit_point(position, name, 100)
    }
    // memo:
    // 関数オーバーロードはないので名前を分けないといけない
    pub fn new_with_hit_point(name: String, position: Vector3, hit_point: i32) -> Self {
        Self {
            position,
            name,
            hit_point: hit_point,
        }
    }

    pub fn damage(&mut self, value: i32) {
        self.hit_point -= value;
    }

    pub fn is_dead(&self) -> bool {
        self.hit_point <= 0
    }
}
// EOF
