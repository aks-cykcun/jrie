/*
 * gsp-keyfile.h: GKeyFile extensions
 *
 * Copyright (C) 2008, 2009 Novell, Inc.
 * Copyright (C) 2016 Tianjin KYLIN Information Technology Co., Ltd.
 *
 * Based on code from panel-keyfile.h (from mate-panel)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * Authors:
 *        Vincent Untz <vuntz@gnome.org>
 * Modified by:
 *        yilei <yilei@kylinos.cn>
 */

#ifndef GSP_KEYFILE_H
#define GSP_KEYFILE_H

#include "glib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GSP_KEY_FILE_DESKTOP_KEY_AUTOSTART_ENABLED "X-UKUI-Autostart-enabled"
#define GSP_KEY_FILE_DESKTOP_KEY_DELAY             "X-UKUI-Autostart-Delay"

void      gsp_key_file_populate        (GKeyFile *keyfile);

gboolean  gsp_key_file_to_file         (GKeyFile       *keyfile,
                                        const gchar    *path,
                                        GError        **error);

gboolean gsp_key_file_get_boolean      (GKeyFile       *keyfile,
                                        const gchar    *key,
                                        gboolean        default_value);
#define gsp_key_file_get_string(key_file, key) \
         g_key_file_get_string (key_file, G_KEY_FILE_DESKTOP_GROUP, key, NULL)
#define gsp_key_file_get_delay(key_file) \
         g_key_file_get_integer (key_file, G_KEY_FILE_DESKTOP_GROUP, GSP_KEY_FILE_DESKTOP_KEY_DELAY, NULL)
#define gsp_key_file_get_locale_string(key_file, key) \
         g_key_file_get_locale_string(key_file, G_KEY_FILE_DESKTOP_GROUP, key, NULL, NULL)

#define gsp_key_file_set_boolean(key_file, key, value) \
         g_key_file_set_boolean (key_file, G_KEY_FILE_DESKTOP_GROUP, key, value)
#define gsp_key_file_set_string(key_file, key, value) \
         g_key_file_set_string (key_file, G_KEY_FILE_DESKTOP_GROUP, key, value)
#define gsp_key_file_set_delay(key_file, value) \
        g_key_file_set_integer(key_file, G_KEY_FILE_DESKTOP_GROUP, GSP_KEY_FILE_DESKTOP_KEY_DELAY, value)
void    gsp_key_file_set_locale_string (GKeyFile    *keyfile,
                                        const gchar *key,
                                        const gchar *value);

void gsp_key_file_ensure_C_key         (GKeyFile   *keyfile,
                                        const char *key);

#ifdef __cplusplus
}
#endif

#endif /* GSP_KEYFILE_H */
