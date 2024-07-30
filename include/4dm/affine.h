#ifndef FDM_4DM_AFFINE_H_2024_07_29_8D1A31FE_3A11_4C16_A5AA_6129EBFAB720
#define FDM_4DM_AFFINE_H_2024_07_29_8D1A31FE_3A11_4C16_A5AA_6129EBFAB720

#include <stddef.h>

typedef struct
{
  float mat[4][4];
  float trans[4];
} fdm_affine;

#define FDM_PVT_DEFINE_AFFINE_MATRIX_READER(name, i, j) \
  static inline float name(fdm_affine const * aff)	\
  {							\
    return aff->mat[i][j];				\
  }

#define FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(name, i, j)			\
  static inline void name(fdm_affine * aff, float new_value)		\
  {									\
    aff->mat[i][j] = new_value;						\
  }

FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_xx, 0, 0)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_xx, 0, 0)
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_xy, 0, 1)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_xy, 0, 1)
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_xz, 0, 2)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_xz, 0, 2)
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_xw, 0, 3)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_xw, 0, 3)
  
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_yx, 1, 0)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_yx, 1, 0)
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_yy, 1, 1)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_yy, 1, 1)
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_yz, 1, 2)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_yz, 1, 2)
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_yw, 1, 3)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_yw, 1, 3)
  
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_zx, 2, 0)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_zx, 2, 0)
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_zy, 2, 1)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_zy, 2, 1)
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_zz, 2, 2)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_zz, 2, 2)
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_zw, 2, 3)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_zw, 2, 3)
  
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_wx, 3, 0)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_wx, 3, 0)
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_wy, 3, 1)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_wy, 3, 1)
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_wz, 3, 2)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_wz, 3, 2)
FDM_PVT_DEFINE_AFFINE_MATRIX_READER(fdm_affine_ww, 3, 3)
FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER(fdm_affine_set_ww, 3, 3)

#undef FDM_PVT_DEFINE_AFFINE_MATRIX_READER
#undef FDM_PVT_DEFINE_AFFINE_MATRIX_WRITER

#define FDM_PVT_DEFINE_AFFINE_TRANS_READER(name, i)	\
  static inline float name(fdm_affine const * aff)	\
  {							\
    return aff->trans[i];				\
  }

#define FDM_PVT_DEFINE_AFFINE_TRANS_WRITER(name, i)		\
  static inline void name(fdm_affine * aff, float new_value)	\
  {								\
    aff->trans[i] = new_value;					\
  }

FDM_PVT_DEFINE_AFFINE_TRANS_READER(fdm_affine_trans_x, 0)
FDM_PVT_DEFINE_AFFINE_TRANS_WRITER(fdm_affine_set_trans_x, 0)
FDM_PVT_DEFINE_AFFINE_TRANS_READER(fdm_affine_trans_y, 1)
FDM_PVT_DEFINE_AFFINE_TRANS_WRITER(fdm_affine_set_trans_y, 1)
FDM_PVT_DEFINE_AFFINE_TRANS_READER(fdm_affine_trans_z, 2)
FDM_PVT_DEFINE_AFFINE_TRANS_WRITER(fdm_affine_set_trans_z, 2)
FDM_PVT_DEFINE_AFFINE_TRANS_READER(fdm_affine_trans_w, 3)
FDM_PVT_DEFINE_AFFINE_TRANS_WRITER(fdm_affine_set_trans_w, 3)

#undef FDM_PVT_DEFINE_AFFINE_TRANS_READER
#undef FDM_PVT_DEFINE_AFFINE_TRANS_WRITER

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

#endif
