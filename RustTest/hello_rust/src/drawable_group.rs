// 文字コード：UTF-8
use crate::drawable::Drawable;

pub struct DrawableGroup<'lt_drawable> {
    drawables: Vec<&'lt_drawable (dyn Drawable + 'lt_drawable)>,
}

impl<'lt_drawable> DrawableGroup<'lt_drawable> {
    pub fn new() -> Self {
        Self {
            drawables: Vec::new(),
        }
    }

    pub fn add(&mut self, drawable: &'lt_drawable dyn Drawable) {
        self.drawables.push(drawable);
    }

    pub fn draw_all(&self) {
        for drawable in &self.drawables {
            drawable.draw();
        }
    }
}
// EOF
