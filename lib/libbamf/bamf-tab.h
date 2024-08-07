/*
 * Copyright 2010-2011 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of either or both of the following licenses:
 *
 * 1) the GNU Lesser General Public License version 3, as published by the
 * Free Software Foundation; and/or
 * 2) the GNU Lesser General Public License version 2.1, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the applicable version of the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of both the GNU Lesser General Public
 * License version 3 and version 2.1 along with this program.  If not, see
 * <http://www.gnu.org/licenses/>
 *
 * Authored by: Jason Smith <jason.smith@canonical.com>
 *              Marco Trevisan (Treviño) <3v1n0@ubuntu.com>
 *
 */

#ifndef __BAMF_TAB_H__
#define __BAMF_TAB_H__

#include <libbamf/bamf-view.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define BAMF_TYPE_TAB                   (bamf_tab_get_type ())

G_DECLARE_DERIVABLE_TYPE (BamfTab, bamf_tab, BAMF, TAB, BamfView);

struct _BamfTabClass
{
  BamfViewClass parent_class;

  const gchar * (*get_desktop_name)         (BamfTab *self);
  const gchar * (*get_location)             (BamfTab *self);
  guint64       (*get_xid)                  (BamfTab *self);
  gboolean      (*get_is_foreground_tab)    (BamfTab *self);

  /*< private >*/
  void (*_tab_padding1) (void);
  void (*_tab_padding2) (void);
  void (*_tab_padding3) (void);
  void (*_tab_padding4) (void);
};

typedef void (*BamfTabPreviewReadyCallback) (BamfTab *self, const gchar *preview_data, gpointer user_data);

gboolean     bamf_tab_raise                 (BamfTab *self);
gboolean     bamf_tab_close                 (BamfTab *self);
void         bamf_tab_request_preview       (BamfTab *self,
                                             BamfTabPreviewReadyCallback callback,
                                             gpointer user_data);
const gchar *bamf_tab_get_desktop_name      (BamfTab *self);
const gchar *bamf_tab_get_location          (BamfTab *self);
guint64      bamf_tab_get_xid               (BamfTab *self);
gboolean     bamf_tab_get_is_foreground_tab (BamfTab *self);

G_END_DECLS

#endif /* __BAMF_TAB_H__ */
