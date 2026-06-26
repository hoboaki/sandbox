// 文字コード：UTF-8
mod character;
mod drawable;
mod drawable_group;
mod math;
mod model;

use crate::character::Character;
use crate::drawable_group::DrawableGroup;

//------------------------------------------------------------------------------
fn main() {
    let v = math::Vector3::new(1.0, 2.0, 3.0);
    println!("{:?}", v.length());

    let mut drawable_group = DrawableGroup::new();
    let chara = Character::new("Pengin", math::Vector3::new(0.0, 0.0, 0.0));
    chara.dump();

    drawable_group.add(chara.model());
    drawable_group.draw_all();
}

//------------------------------------------------------------------------------
// EOF
