
#include <stddef.h>

#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/TestDB.h>

#include <4dm/vector.h>

#define EPSILON 0.001

#define ASSERT_VECTOR_EQUAL(vect, x, y, z, w)			\
  {								\
    CU_ASSERT_DOUBLE_EQUAL(x, fdm_vector_x(&vect), EPSILON);	\
    CU_ASSERT_DOUBLE_EQUAL(y, fdm_vector_y(&vect), EPSILON);	\
    CU_ASSERT_DOUBLE_EQUAL(z, fdm_vector_z(&vect), EPSILON);	\
    CU_ASSERT_DOUBLE_EQUAL(w, fdm_vector_w(&vect), EPSILON);	\
  }

void fdm_vector_basic_test(void)
{
  fdm_vector vect = fdm_create_vector(-51, 93, 29, 84);
  ASSERT_VECTOR_EQUAL(vect, -51, 93, 29, 84);

  fdm_vector_set_x(&vect, 32);
  fdm_vector_set_y(&vect, 37);
  fdm_vector_set_z(&vect, -14);
  fdm_vector_set_w(&vect, -82);
  ASSERT_VECTOR_EQUAL(vect, 32, 37, -14, -82);
}

void fdm_vector_arith_test(void)
{
  fdm_vector vect1 = fdm_create_vector(29, -93, 67, 14);
  fdm_vector vect2 = fdm_create_vector(-35, -70, 31, 12);
  fdm_vector result;

  result = fdm_vector_add(&vect1, &vect2);
  ASSERT_VECTOR_EQUAL(result, -6, -163, 98, 26)

  result = fdm_vector_subtract(&vect1, &vect2);
  ASSERT_VECTOR_EQUAL(result, 64, -23, 36, 2);

  result = fdm_vector_multiply(&vect1, 75);
  ASSERT_VECTOR_EQUAL(result, 2175, -6975, 5025, 1050);

  result = fdm_vector_combine(-8, &vect1, 9, &vect2);
  ASSERT_VECTOR_EQUAL(result, -547, 114, -257, -4);
}

void fdm_vector_topo_test(void)
{
  fdm_vector vect1 = fdm_create_vector(64, -76, -12, 32);
  fdm_vector vect2 = fdm_create_vector(-19, -1, -59, 13);
  fdm_vector vect3 = fdm_create_vector(95, 64, -2, 95);
  fdm_vector vect4 = fdm_create_vector(42, 28, 5, -2);
  float sresult;
  fdm_vector vresult;

  sresult = fdm_vector_dot(&vect1, &vect2);
  CU_ASSERT_DOUBLE_EQUAL(-16, sresult, EPSILON);
  
  sresult = fdm_vector_norm_2(&vect1);
  CU_ASSERT_DOUBLE_EQUAL(11040, sresult, EPSILON);

  sresult = fdm_vector_norm(&vect1);
  CU_ASSERT_DOUBLE_EQUAL(105.0714043, sresult, EPSILON);

  vresult = fdm_vector_normalize(&vect1);
  ASSERT_VECTOR_EQUAL(vresult, 0.6091095, -0.7233176, -0.1142080, 0.3045547);

  vresult = fdm_vector_cross(&vect1, &vect2, &vect3);
  ASSERT_VECTOR_EQUAL(vresult, 533776, 212960, -326240, -684112);
  CU_ASSERT_DOUBLE_EQUAL(0, fdm_vector_dot(&vect1, &vresult), EPSILON);
  CU_ASSERT_DOUBLE_EQUAL(0, fdm_vector_dot(&vect2, &vresult), EPSILON);
  CU_ASSERT_DOUBLE_EQUAL(0, fdm_vector_dot(&vect3, &vresult), EPSILON);
  
  sresult = fdm_determinant(&vect1, &vect2, &vect3, &vect4);
  CU_ASSERT_DOUBLE_EQUAL(-28118496, sresult, EPSILON);

  CU_ASSERT_FALSE(fdm_orientation(&vect1, &vect2, &vect3, &vect4));
}

int main(void)
{
  CU_initialize_registry();
  
  CU_pSuite suite = CU_add_suite("fdm_vector test", NULL, NULL);
  CU_add_test(suite, "fdm_vector basic test", fdm_vector_basic_test);
  CU_add_test(suite, "fdm_vector arith test", fdm_vector_arith_test);
    CU_add_test(suite, "fdm_vector topo test", fdm_vector_topo_test);
    
  CU_console_run_tests();
  CU_cleanup_registry();
  return 0;
}
