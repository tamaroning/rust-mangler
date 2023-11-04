struct S();

pub mod mod_a {
    pub fn f() {}
}

pub fn generic_func<T>(t: T) -> T {
    t
}

pub fn main() {
    mod_a::f();

    let f = |a: i32| a + 1;
    let _ = f(1);

    generic_func::<i32>(0);
    generic_func::<S>(S());
}
