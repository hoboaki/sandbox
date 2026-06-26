// 文字コード：UTF-8
use crate::drawable::Drawable;

pub struct Model {
    pub name: String,
}

impl Drawable for Model {
    fn draw(&self) {
        println!("Drawing model: {}", self.name);
    }
}
// EOF
