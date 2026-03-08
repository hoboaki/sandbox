// 文字コード：UTF-8

#[derive(Debug, Copy, Clone)]
pub struct Vector3 {
    x: f32,
    y: f32,
    z: f32,
}

impl Vector3 {
    pub fn new(x: f32, y: f32, z: f32) -> Self {
        Self { x, y, z }
    }

    // memo:
    // const 参照渡しする場合は `other: &Vector3` と書く。
    // 非 const 参照は `other: &mut Vector3` と書く.
    pub fn dot(self, other: Self) -> f32 {
        self.x * other.x + self.y * other.y + self.z * other.z
    }

    pub fn length(self) -> f32 {
        self.dot(self).sqrt()
    }
}

//------------------------------------------------------------------------------
// EOF
