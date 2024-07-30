#ifndef FDM_4DM_UTIL_H_2024_07_30_02717754_EDF6_45FD_BA8F_8F731F8196C9
#define FDM_4DM_UTIL_H_2024_07_30_02717754_EDF6_45FD_BA8F_8F731F8196C9

#define FDM_PI 3.1415926535897932384626433832795028841971

static inline float fdm_to_radian(float degree)
{
  return degree * FDM_PI / 180;
}

static inline float fdm_to_degree(float radian)
{
  return radian * 180 / FDM_PI;
}

#endif
