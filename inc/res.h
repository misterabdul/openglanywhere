#ifndef __RES_H__
#define __RES_H__

/**
 * @brief Embedded resources data.
 *
 * All the resource in res directory listed here with example format:
 *   res/shaders/cube.fs => res_shaders_cube_fs
 */

extern unsigned char res_shaders_cube_fs[];
extern unsigned int res_shaders_cube_fs_len;
extern unsigned char res_shaders_cube_es_fs[];
extern unsigned int res_shaders_cube_es_fs_len;

extern unsigned char res_shaders_cube_vs[];
extern unsigned int res_shaders_cube_vs_len;
extern unsigned char res_shaders_cube_es_vs[];
extern unsigned int res_shaders_cube_es_vs_len;

extern unsigned char res_images_awesomeface_png[];
extern unsigned int res_images_awesomeface_png_len;
extern unsigned char res_images_container_jpg[];
extern unsigned int res_images_container_jpg_len;

#endif
