
#include <stddef.h>

#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/TestDB.h>

#include <4dm.h>

#define EPSILON 0.001

#define ASSERT_VECTOR_EQUAL(vect, x, y, z, w)			\
  {								\
    CU_ASSERT_DOUBLE_EQUAL(x, fdm_vector_x(&vect), EPSILON);	\
    CU_ASSERT_DOUBLE_EQUAL(y, fdm_vector_y(&vect), EPSILON);	\
    CU_ASSERT_DOUBLE_EQUAL(z, fdm_vector_z(&vect), EPSILON);	\
    CU_ASSERT_DOUBLE_EQUAL(w, fdm_vector_w(&vect), EPSILON);	\
  }

#define ASSERT_AFFINE_EQUAL(aff,					\
			    xx,  xy,  xz,  xw,				\
			    yx,  yy,  yz,  yw,				\
			    zx,  zy,  zz,  zw,				\
			    wx,  wy,  wz,  ww,				\
			    trans_x, trans_y,				\
			    trans_z, trans_w)				\
  {									\
    CU_ASSERT_DOUBLE_EQUAL(xx, fdm_affine_xx(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(xy, fdm_affine_xy(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(xz, fdm_affine_xz(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(xw, fdm_affine_xw(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(yx, fdm_affine_yx(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(yy, fdm_affine_yy(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(yz, fdm_affine_yz(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(yw, fdm_affine_yw(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(zx, fdm_affine_zx(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(zy, fdm_affine_zy(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(zz, fdm_affine_zz(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(zw, fdm_affine_zw(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(wx, fdm_affine_wx(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(wy, fdm_affine_wy(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(wz, fdm_affine_wz(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(ww, fdm_affine_ww(&aff), EPSILON);		\
    CU_ASSERT_DOUBLE_EQUAL(trans_x, fdm_affine_trans_x(&aff), EPSILON);	\
    CU_ASSERT_DOUBLE_EQUAL(trans_y, fdm_affine_trans_y(&aff), EPSILON);	\
    CU_ASSERT_DOUBLE_EQUAL(trans_z, fdm_affine_trans_z(&aff), EPSILON);	\
    CU_ASSERT_DOUBLE_EQUAL(trans_w, fdm_affine_trans_w(&aff), EPSILON);	\
  }


void fdm_affine_ctor_test(void)
{
  fdm_affine aff = fdm_create_matrix(-48, -23, -13, -14,
				     -99, 9, -50, 19,
				     -68, 18, 72, 98,
				     40, -59, -90, 10);
  ASSERT_AFFINE_EQUAL(aff,
		      -48, -23, -13, -14,
		      -99, 9, -50, 19,
		      -68, 18, 72, 98,
		      40, -59, -90, 10,
		      0, 0, 0, 0);

  aff = fdm_create_translate(53, 20, -33, 81);
  ASSERT_AFFINE_EQUAL(aff,
		      1, 0, 0, 0,
		      0, 1, 0, 0,
		      0, 0, 1, 0,
		      0, 0, 0, 1,
		      53, 20, -33, 81);

  aff = fdm_create_scale(-24, -89, -4, 5);
  ASSERT_AFFINE_EQUAL(aff,
		      -24, 0, 0, 0,
		      0, -89, 0, 0,
		      0, 0, -4, 0,
		      0, 0, 0, 5,
		      0, 0, 0, 0);

  aff = fdm_create_identity_affine();
  ASSERT_AFFINE_EQUAL(aff,
		      1, 0, 0, 0,
		      0, 1, 0, 0,
		      0, 0, 1, 0,
		      0, 0, 0, 1,
		      0, 0, 0, 0);

  fdm_affine_set_xx(&aff, -34);
  fdm_affine_set_xy(&aff, 38);
  fdm_affine_set_xz(&aff, -42);
  fdm_affine_set_xw(&aff, -50);
  fdm_affine_set_yx(&aff, 20);
  fdm_affine_set_yy(&aff, 36);
  fdm_affine_set_yz(&aff, 32);
  fdm_affine_set_yw(&aff, 87);
  fdm_affine_set_zx(&aff, 86);
  fdm_affine_set_zy(&aff, -33);
  fdm_affine_set_zz(&aff, -16);
  fdm_affine_set_zw(&aff, -5);
  fdm_affine_set_wx(&aff, 72);
  fdm_affine_set_wy(&aff, -10);
  fdm_affine_set_wz(&aff, -45);
  fdm_affine_set_ww(&aff, -60);
  fdm_affine_set_trans_x(&aff, 25);
  fdm_affine_set_trans_y(&aff, 74);
  fdm_affine_set_trans_z(&aff, 67);
  fdm_affine_set_trans_w(&aff, 65);
  ASSERT_AFFINE_EQUAL(aff,
		      -34, 38, -42, -50,
		      20, 36, 32, 87,
		      86, -33, -16, -5,
		      72, -10, -45, -60,
		      25, 74, 67, 65);
}

void fdm_affine_str_test(void)
{
  fdm_affine aff = {
    {
      { -51, 38, -43, 92 },
      { 50, -69, 60, 90 },
      { 87, -39, 43, 88 },
      { 54, 65, -2, 99 }
    },
    { -64, 94, -71, 5 }
  };
  fdm_affine aff2 = {
    {
      { -3, -10, -8, -1 },
      { -7, 5, 5, 8 },
      { -8, 8, 6, -10 },
      { 7, 3, 5, 8 }
    },
    { -8, -7, -4, -4 }
  };
  fdm_vector vect = fdm_create_vector(-98, -73, -78, -24);

  fdm_vector result = fdm_affine_apply(&aff, &vect);
  ASSERT_VECTOR_EQUAL(result, 3306, -6609, -11216, -12252);

  fdm_affine aresult = fdm_affine_concat(&aff, &aff2);
  ASSERT_AFFINE_EQUAL(aresult,
		      -1097, 823, -813, -1979,
		      1474, -286, 800, 1038,
		      790, -1740, 1102, -478,
		      660, 384, 78, 2146,
		      -193, 596, 784, -485);
}

int main(void)
{
  CU_initialize_registry();
  
  CU_pSuite suite = CU_add_suite("fdm_affine test", NULL, NULL);
  CU_add_test(suite, "fdm_affine ctor test", fdm_affine_ctor_test);
  CU_add_test(suite, "fdm_affine str test", fdm_affine_str_test);
  
  CU_console_run_tests();
  CU_cleanup_registry();
  return 0;
}
