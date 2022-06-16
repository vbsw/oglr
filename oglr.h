#ifndef OGLR_H
#define OGLR_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(OGLR_WIN32)
typedef unsigned long oglr_ul_t;
extern void oglr_error(void *err, int *err_num, oglr_ul_t *err_win32, char **err_str);
extern void oglr_error_free(void *data);
extern void oglr_init(void **err);
extern void oglr_free(void *data);
#elif defined(OGLR_X)
#endif

#ifdef __cplusplus
}
#endif

#endif /* OGLR_H */