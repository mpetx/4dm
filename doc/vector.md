
型`fdm_vector`に関する関数についてのドキュメントです。

## 型 `fdm_vector`

```c
typedef /* [...] */ fdm_vector;
```

４次元ベクトルを表す型。

## 関数 `fdm_create_vector`

```c
fdm_vector fdm_create_vector(float x, float y, float z, float w);
```

ベクトルを作成します。

## 関数 `fdm_vector_X`
```c
fdm_vector fdm_vector_x(fdm_vector const * vect);
fdm_vector fdm_vector_y(fdm_vector const * vect);
fdm_vector fdm_vector_z(fdm_vector const * vect);
fdm_vector fdm_vector_w(fdm_vector const * vect);
```

ベクトルの各要素を取り出します。

## 関数 `fdm_vector_set_X`
```c
void fdm_vector_set_x(fdm_vector * vect, float new_value);
void fdm_vector_set_y(fdm_vector * vect, float new_value);
void fdm_vector_set_z(fdm_vector * vect, float new_value);
void fdm_vector_set_w(fdm_vector * vect, float new_value);
```

ベクトルの各要素の値を変更します。

## 関数 `fdm_vector_add`, `fdm_vector_subtract`, `fdm_vector_multiply`
```c
fdm_vector fdm_vector_add(fdm_vector const * lhs, fdm_vector const * rhs);
fdm_vector fdm_vector_subtract(fdm_vector const * lhs, fdm_vector const * rhs);
fdm_vector fdm_vector_multiply(fdm_vector const * lhs, float c);
```

ベクトルの和、差、スカラー倍を計算します。

## 関数 `fdm_vector_combine`
```c
fdm_vector fdm_vector_combine(float c1, fdm_vector const * vect1, float c2, fdm_vector const * vect2);
```

ベクトルの線形結合 (`c1 * vect1 + c2 * vect2`) を計算します。

## 関数 `fdm_vector_dot`
```c
float fdm_vector_dot(fdm_vector const * lhs, fdm_vector const * rhs);
```

ベクトルの内積を計算します。

## 関数 `fdm_vector_norm`
```c
float fdm_vector_norm(fdm_vector const * vect);
float fdm_vector_norm_2(fdm_vector const * vect)
```

`fdm_vector_norm`はベクトルのノルムを計算します。

`fdm_vector_norm2`はベクトルのノルムの２乗を計算します。

## 関数 `fdm_vector_normalize`
```c
fdm_vector fdm_vector_normalize(fdm_vector const * vect);
```

ベクトルを単位ベクトル化します。

ベクトルが零ベクトルである場合の動作は未定義です。

## 関数 `fdm_vector_cross`
```c
fdm_vector fdm_vector_cross(fdm_vector const * vect1, fdm_vector const * vect2, fdm_vector const * vect3);
```

ベクトルの外積を計算します。

## 関数 `fdm_determinant`
```c
float fdm_determinant(fdm_vector const * vect1, fdm_vector const * vect2, fdm_vector const * vect3, fdm_vector const * vect4);
```

ベクトルを４つ並べた行列の行列式を計算します。

## 関数 `fdm_orientation`
```c
bool fdm_orientation(fdm_vector const * vect1, fdm_vector const * vect2, fdm_vector const * vect3, fdm_vector const * vect4);
```

４つのベクトルが成す多胞体の向きを計算します。多胞体が

```math
\vec{e}_\mathrm{x} \wedge \vec{e}_\mathrm{y} \wedge \vec{e}_\mathrm{z} \wedge \vec{e}_\mathrm{w}
```

と同じ向きを持つ場合は`true`を、そうでない場合は`false`を返します。

多胞体が退化している場合の動作は未定義です。
