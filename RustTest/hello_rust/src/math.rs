// 文字コード：UTF-8
mod vector3; // math/vector3.rs の pub 要素を使えるようにする。`math/` が省略できるのは rust の仕様。
pub use vector3::Vector3; // これで Vector3 という名前でアクセスできるようにする。
// EOF
