#ifndef FDM_4DM_AFFINE_H_2024_07_29_8D1A31FE_3A11_4C16_A5AA_6129EBFAB720
#define FDM_4DM_AFFINE_H_2024_07_29_8D1A31FE_3A11_4C16_A5AA_6129EBFAB720

#include <stddef.h>
#include <math.h>

typedef struct
{
  float mat[4][4];
  float trans[4];
} fdm_affine;

#define FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(reader_name, writer_name, i, j) \
  static inline float reader_name(fdm_affine const * aff)		\
  {									\
    return aff->mat[i][j];						\
  }									\
  static inline void writer_name(fdm_affine * aff, float new_value)	\
  {									\
    aff->mat[i][j] = new_value ;					\
  }

FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_xx, fdm_affine_set_xx, 0, 0)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_xy, fdm_affine_set_xy, 0, 1)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_xz, fdm_affine_set_xz, 0, 2)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_xw, fdm_affine_set_xw, 0, 3)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_yx, fdm_affine_set_yx, 1, 0)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_yy, fdm_affine_set_yy, 1, 1)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_yz, fdm_affine_set_yz, 1, 2)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_yw, fdm_affine_set_yw, 1, 3)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_zx, fdm_affine_set_zx, 2, 0)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_zy, fdm_affine_set_zy, 2, 1)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_zz, fdm_affine_set_zz, 2, 2)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_zw, fdm_affine_set_zw, 2, 3)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_wx, fdm_affine_set_wx, 3, 0)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_wy, fdm_affine_set_wy, 3, 1)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_wz, fdm_affine_set_wz, 3, 2)
FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR(fdm_affine_ww, fdm_affine_set_ww, 3, 3)

#undef FDM_PVT_DEFINE_AFFINE_MATRIX_ACCESSOR

#define FDM_PVT_DEFINE_AFFINE_TRANS_ACCESSOR(reader_name, writer_name, i) \
  static inline float reader_name(fdm_affine const * aff)		\
  {									\
    return aff->trans[i];						\
  }									\
  static inline void writer_name(fdm_affine * aff, float new_value)	\
  {									\
    aff->trans[i] = new_value;						\
  }

FDM_PVT_DEFINE_AFFINE_TRANS_ACCESSOR(fdm_affine_trans_x, fdm_affine_set_trans_x, 0)
FDM_PVT_DEFINE_AFFINE_TRANS_ACCESSOR(fdm_affine_trans_y, fdm_affine_set_trans_y, 1)
FDM_PVT_DEFINE_AFFINE_TRANS_ACCESSOR(fdm_affine_trans_z, fdm_affine_set_trans_z, 2)
FDM_PVT_DEFINE_AFFINE_TRANS_ACCESSOR(fdm_affine_trans_w, fdm_affine_set_trans_w, 3)

#undef FDM_PVT_DEFINE_AFFINE_TRANS_ACCESSOR

static inline fdm_affine fdm_create_matrix(float xx, float xy, float xz, float xw,
					   float yx, float yy, float yz, float yw,
					   float zx, float zy, float zz, float zw,
					   float wx, float wy, float wz, float ww)
{
  return (fdm_affine) {
    {
      { xx, xy, xz, xw },
      { yx, yy, yz, yw },
      { zx, zy, zz, zw },
      { wx, wy, wz, ww }
    },
    { 0, 0, 0, 0 }
  };
}

static inline fdm_affine fdm_create_translate(float x, float y, float z, float w)
{
  return (fdm_affine) {
    {
      { 1, 0, 0, 0 },
      { 0, 1, 0, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 0, 1 }
    },
    { x, y, z, w }
  };
}

static inline fdm_affine fdm_create_scale(float x, float y, float z, float w)
{
  return (fdm_affine) {
    {
      { x, 0, 0, 0 },
      { 0, y, 0, 0 },
      { 0, 0, z, 0 },
      { 0, 0, 0, w }
    },
    { 0, 0, 0, 0 }
  };
}

static inline fdm_affine fdm_create_identity_affine()
{
  return fdm_create_scale(1, 1, 1, 1);
}

static inline fdm_vector fdm_affine_apply(fdm_affine const * aff, fdm_vector const * vect)
{
  fdm_vector result = fdm_create_vector(0, 0, 0, 0);
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j)
      result.data[i] += aff->mat[i][j] * vect->data[j];
    result.data[i] += aff->trans[i];
  }
  return result;
}

static inline fdm_affine fdm_affine_concat(fdm_affine const * aff1, fdm_affine const * aff2)
{
  fdm_affine result = { 0 };
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      for (size_t k = 0; k < 4; ++k)
	result.mat[i][j] += aff2->mat[i][k] * aff1->mat[k][j];
    }
    for (size_t k = 0; k < 4; ++k)
      result.trans[i] += aff2->mat[i][k] * aff1->trans[k];
    result.trans[i] += aff2->trans[i];
  }
  return result;
}

static inline fdm_affine fdm_create_rotate(float rad, fdm_vector const * vect1, fdm_vector const * vect2)
{
  // <u1,u2> = <vect1,vect2> を満たす正規直交基底u1~u4を見つける
  fdm_vector u1 = fdm_vector_normalize(vect1);
  fdm_vector u2 = *vect2;
  fdm_vector as[4] = {
    fdm_create_vector(1, 0, 0, 0),
    fdm_create_vector(0, 1, 0, 0),
    fdm_create_vector(0, 0, 1, 0),
    fdm_create_vector(0, 0, 0, 1)
  };
  u2 = fdm_vector_combine(1, &u2, -fdm_vector_dot(&u1, &u2), &u1);
  for (size_t i = 0; i < 4; ++i)
    as[i] = fdm_vector_combine(1, as+i, -fdm_vector_dot(&u1, as+i), &u1);
  u2 = fdm_vector_normalize(&u2);
  for (size_t i = 0; i < 4; ++i)
    as[i] = fdm_vector_combine(1, as+i, -fdm_vector_dot(&u2, as+i), &u2);
  float max_norm = fdm_vector_norm_2(as);
  size_t max_ind = 0;
  for (size_t i = 1; i < 4; ++i) {
    float norm = fdm_vector_norm_2(as+i);
    if (norm > max_norm) {
      max_norm = norm;
      max_ind = i;
    }
  }
  fdm_vector u3 = fdm_vector_normalize(as+max_ind);
  as[max_ind] = as[3];
  for (size_t i = 0; i < 3; ++i)
    as[i] = fdm_vector_combine(1, as+i, -fdm_vector_dot(&u3, as+i), &u3);
  max_norm = fdm_vector_norm_2(as);
  max_ind = 0;
  for (size_t i = 1; i < 3; ++i) {
    float norm = fdm_vector_norm_2(as+i);
    if (norm > max_norm) {
      max_norm = norm;
      max_ind = i;
    }
  }
  fdm_vector u4 = fdm_vector_normalize(as+max_ind);

  fdm_affine basis_change = fdm_create_matrix
    (fdm_vector_x(&u1), fdm_vector_y(&u1), fdm_vector_z(&u1), fdm_vector_w(&u1),
     fdm_vector_x(&u2), fdm_vector_y(&u2), fdm_vector_z(&u2), fdm_vector_w(&u2),
     fdm_vector_x(&u3), fdm_vector_y(&u3), fdm_vector_z(&u3), fdm_vector_w(&u3),
     fdm_vector_x(&u4), fdm_vector_y(&u4), fdm_vector_z(&u4), fdm_vector_w(&u4));
  fdm_affine rotate = fdm_create_matrix
    (cosf(rad), -sinf(rad), 0, 0,
     sinf(rad), cos(rad), 0, 0,
     0, 0, 1, 0,
     0, 0, 0, 1);
  fdm_affine basis_dischange = fdm_create_matrix
    (fdm_vector_x(&u1), fdm_vector_x(&u2), fdm_vector_x(&u3), fdm_vector_x(&u4),
     fdm_vector_y(&u1), fdm_vector_y(&u2), fdm_vector_y(&u3), fdm_vector_y(&u4),
     fdm_vector_z(&u1), fdm_vector_z(&u2), fdm_vector_z(&u3), fdm_vector_z(&u4),
     fdm_vector_w(&u1), fdm_vector_w(&u2), fdm_vector_w(&u3), fdm_vector_w(&u4));
  fdm_affine result = fdm_affine_concat(&basis_change, &rotate);
  result = fdm_affine_concat(&result, &basis_dischange);
  return result;
}

#endif
