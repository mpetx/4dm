
型`fdm_affine`に関する関数についてのドキュメントです。

## 型 `fdm_affine`
```c
typedef /* [...] */ fdm_affine
```

アフィン変換を表す型。

## 関数 `fdm_affine_XY`
```c
float fdm_affine_xx(fdm_affine const * aff);
float fdm_affine_xy(fdm_affine const * aff);
/* [...] */
float fdm_affine_ww(fdm_affine const * aff);
```

アフィン変換の行列部分の各要素を取り出します。

## 関数 `fdm_affine_set_XY`
```c
void fdm_affine_set_xx(fdm_affine * aff, float new_value);
void fdm_affine_set_xy(fdm_affine * aff, float new_value);
/* [...] */
void fdm_affine_set_ww(fdm_affine * aff, float new_value);
```

アフィン変換の行列部分の各要素の値を変更します。

## 関数 `fdm_affine_trans_X`
```c
float fdm_affine_trans_x(fdm_affine const * aff);
float fdm_affine_trans_y(fdm_affine const * aff);
float fdm_affine_trans_z(fdm_affine const * aff);
float fdm_affine_trans_w(fdm_affine const * aff);
```

アフィン変換の平行移動部分の各要素の値を取り出します。

## 関数 `fdm_affine_set_trans_X`
```c
void fdm_affine_set_trans_x(fdm_affine * aff, float new_value);
void fdm_affine_set_trans_y(fdm_affine * aff, float new_value);
void fdm_affine_set_trans_z(fdm_affine * aff, float new_value);
void fdm_affine_set_trans_w(fdm_affine * aff, float new_value);
```

アフィン変換の平行移動部分の各要素の値を変更します。

## 関数 `fdm_create_identity_affine`
```c
fdm_affine fdm_create_identity_affine();
```

恒等変換を表すアフィン変換を作成します。

## 関数 `fdm_create_matrix`
```c
fdm_affine fdm_create_matrix(
  float xx, float xy, float xz, float xw,
  float yx, float yy, float yz, float yw,
  float zx, float zy, float zz, float zw,
  float wx, float wy, float wz, float ww);
```

線形変換を表すアフィン変換を作成します。

## 関数 `fdm_create_translate`
```c
fdm_affine fdm_create_translate(float x, float y, float z, float w);
```

平行移動を表すアフィン変換を作成します。

## 関数 `fdm_create_scale`
```c
fdm_affine fdm_create_scale(float x, float y, float z, float w);
```

スケール変換を表すアフィン変換を作成します。

## 関数 `fdm_create_rotate`
```c
fdm_affine fdm_create_rotate(float rad, fdm_vector const * vect1, fdm_vector const * vect2);
fdm_affine fdm_create_double_rotate(float rad1, float rad2, fdm_vector const * vect1, fdm_vector const * vect2);
```

回転変換を表すアフィン変換を作成します。

`fdm_create_rotate`は`vect1`と`vect2`が成す平面 $S$ を`vect1`から`vect2`の方向に`rad`ラジアンだけ回転させます。`fdm_create_double_rotate`はさらに平面 $S$ と垂直な平面 $T$ を`rad2`ラジアン回転させます。回転の方向は $S \wedge T$ が正の向きとなるように選ばれます。

## 関数 `fdm_affine_apply`
```c
fdm_vector fdm_affine_apply(fdm_affine const * aff, fdm_vector const * vect);
```

アフィン変換をベクトルに適用します。

## 関数 `fdm_affine_concat`
```c
fdm_affine fdm_affine_concat(fdm_affine const * aff1, fdm_affine const * aff2)
```

アフィン変換の合成を計算します。`aff1`が先であることに注意してください。つまり、この関数の返り値は合成演算子 $\circ$ を使って

```math
 \mathrm{Aff}_2 \circ \mathrm{Aff}_1
```

と書けます。
