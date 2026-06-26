// 文字コード：UTF-8
use crate::math::Vector3;
use crate::model::Model;

pub struct Character {
    pub position: Vector3,
    pub name: String,
    pub hit_point: i32,
    model: Model,
}

impl Character {
    pub fn new(name: &str, position: Vector3) -> Self {
        Self::new_with_hit_point(name, position, 100)
    }
    // memo:
    // 関数オーバーロードはないので名前を分けないといけない
    pub fn new_with_hit_point(name: &str, position: Vector3, hit_point: i32) -> Self {
        Self {
            position: position,
            name: name.to_string(),
            hit_point: hit_point,
            model: Model {
                name: name.to_string(),
            },
        }
    }

    // pub fn damage(&mut self, value: i32) {
    //     self.hit_point -= value;
    // }

    // pub fn is_dead(&self) -> bool {
    //     self.hit_point <= 0
    // }

    pub fn dump(&self) {
        println!(
            "Character: name={}, position=({:.1}, {:.1}, {:.1}), hit_point={}",
            self.name, self.position.x, self.position.y, self.position.z, self.hit_point
        );
    }

    pub fn model(&self) -> &Model {
        &self.model
    }
}
// EOF
