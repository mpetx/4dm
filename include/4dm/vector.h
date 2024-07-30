#ifndef FDM_4DM_VECTOR_H_2024_07_29_BD598C4E_CF1D_46DC_AE20_416BF761DE5C
#define FDM_4DM_VECTOR_H_2024_07_29_BD598C4E_CF1D_46DC_AE20_416BF761DE5C

#include <stdbool.h>
#include <stddef.h>
#include <math.h>

typedef struct
{
  float data[4];
} fdm_vector;

static inline fdm_vector fdm_create_vector(float x, float y, float z, float w)
{
  return (fdm_vector) {
    { x, y, z, w }
  };
}

#define FDM_PVT_DEFINE_VECTOR_ACCESSOR(reader_name, writer_name, offset) \
  static inline float reader_name(fdm_vector const * vect)		\
  {									\
    return vect->data[offset];						\
  }									\
  static inline void writer_name(fdm_vector * vect, float new_value)	\
  {									\
    vect->data[offset] = new_value;					\
  }

FDM_PVT_DEFINE_VECTOR_ACCESSOR(fdm_vector_x, fdm_vector_set_x, 0)
FDM_PVT_DEFINE_VECTOR_ACCESSOR(fdm_vector_y, fdm_vector_set_y, 1)
FDM_PVT_DEFINE_VECTOR_ACCESSOR(fdm_vector_z, fdm_vector_set_z, 2)
FDM_PVT_DEFINE_VECTOR_ACCESSOR(fdm_vector_w, fdm_vector_set_w, 3)

#undef FDM_PVT_DEFINE_VECTOR_ACCESSOR

#define FDM_PVT_DEFINE_VECTOR_BINARY_ARITHMETIC(name, op)		\
  static inline fdm_vector name(fdm_vector const * lhs, fdm_vector const * rhs) \
  {									\
    fdm_vector result;							\
    for (size_t i = 0; i < 4; ++i)					\
      result.data[i] = op(lhs->data[i], rhs->data[i]);			\
    return result;							\
  }

#define FDM_PVT_ADD(lhs, rhs) ((lhs) + (rhs))
FDM_PVT_DEFINE_VECTOR_BINARY_ARITHMETIC(fdm_vector_add, FDM_PVT_ADD)
#define FDM_PVT_SUBTRACT(lhs, rhs) ((lhs) - (rhs))
FDM_PVT_DEFINE_VECTOR_BINARY_ARITHMETIC(fdm_vector_subtract, FDM_PVT_SUBTRACT)

#undef FDM_PVT_DEFINE_VECTOR_BINARY_ARITHMETIC
#undef FDM_PVT_ADD
#undef FDM_PVT_SUBTRACT

static inline fdm_vector fdm_vector_multiply(fdm_vector const * vect, float c)
{
  return fdm_create_vector
    (c * fdm_vector_x(vect),
     c * fdm_vector_y(vect),
     c * fdm_vector_z(vect),
     c * fdm_vector_w(vect));
}

static inline fdm_vector fdm_vector_combine(float c1, fdm_vector const * vect1, float c2, fdm_vector const * vect2)
{
  return fdm_create_vector
    (c1 * fdm_vector_x(vect1) + c2 * fdm_vector_x(vect2),
     c1 * fdm_vector_y(vect1) + c2 * fdm_vector_y(vect2),
     c1 * fdm_vector_z(vect1) + c2 * fdm_vector_z(vect2),
     c1 * fdm_vector_w(vect1) + c2 * fdm_vector_w(vect2));
}

static inline float fdm_vector_dot(fdm_vector const * lhs, fdm_vector const * rhs)
{
  float result = 0;
  for (size_t i = 0; i < 4; ++i)
    result += lhs->data[i] * rhs->data[i];
  return result;
}

static inline float fdm_vector_norm_2(fdm_vector const * vect)
{
  return fdm_vector_dot(vect, vect);
}

static inline float fdm_vector_norm(fdm_vector const * vect)
{
  return sqrtf(fdm_vector_norm_2(vect));
}

static inline fdm_vector fdm_vector_normalize(fdm_vector const * vect)
{
  float norm = fdm_vector_norm(vect);
  return fdm_vector_multiply(vect, 1 / norm);
}

#define FDM_PVT_DETERMINANT_3(obj1, obj2, obj3, x, y, z)		\
  (x(obj1) * y(obj2) * z(obj3) + y(obj1) * z(obj2) * x(obj3) + z(obj1) * x(obj2) * y(obj3) \
   - z(obj1) * y(obj2) * x(obj3) - y(obj1) * x(obj2) * z(obj3) - x(obj1) * z(obj2) * y(obj3)) 

static inline fdm_vector fdm_vector_cross(fdm_vector const * vect1, fdm_vector const * vect2, fdm_vector const * vect3)
{
  return fdm_create_vector
    (FDM_PVT_DETERMINANT_3(vect1, vect2, vect3, fdm_vector_y, fdm_vector_z, fdm_vector_w),
     -FDM_PVT_DETERMINANT_3(vect1, vect2, vect3, fdm_vector_x, fdm_vector_z, fdm_vector_w),
     FDM_PVT_DETERMINANT_3(vect1, vect2, vect3, fdm_vector_x, fdm_vector_y, fdm_vector_w),
     -FDM_PVT_DETERMINANT_3(vect1, vect2, vect3, fdm_vector_x, fdm_vector_y, fdm_vector_z));
}

static inline float fdm_determinant(fdm_vector const * vect1, fdm_vector const * vect2, fdm_vector const * vect3, fdm_vector const * vect4)
{
  return fdm_vector_x(vect1) * FDM_PVT_DETERMINANT_3(vect2, vect3, vect4, fdm_vector_y, fdm_vector_z, fdm_vector_w)
    - fdm_vector_y(vect1) * FDM_PVT_DETERMINANT_3(vect2, vect3, vect4, fdm_vector_x, fdm_vector_z, fdm_vector_w)
    + fdm_vector_z(vect1) * FDM_PVT_DETERMINANT_3(vect2, vect3, vect4, fdm_vector_x, fdm_vector_y, fdm_vector_w)
    - fdm_vector_w(vect1) * FDM_PVT_DETERMINANT_3(vect2, vect3, vect4, fdm_vector_x, fdm_vector_y, fdm_vector_z);
}

static inline bool fdm_orientation(fdm_vector const * vect1, fdm_vector const * vect2, fdm_vector const * vect3, fdm_vector const * vect4)
{
  float det = fdm_determinant(vect1, vect2, vect3, vect4);
  return det > 0;
}

#undef FDM_PVT_DETERMINANT_3

#endif
