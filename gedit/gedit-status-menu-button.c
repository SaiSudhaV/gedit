/*
 * gedit-status-menu-button.c
 * This file is part of gedit
 *
 * Copyright (C) 2008 - Jesse van den Kieboom
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "gedit-status-menu-button.h"

struct _GeditStatusMenuButtonPrivate
{
	GtkWidget *label;
};

struct _GeditStatusMenuButtonClassPrivate
{
	GtkCssProvider *css;
};

/* Properties */
enum
{
	PROP_0,
	PROP_LABEL
};

G_DEFINE_TYPE_WITH_CODE (GeditStatusMenuButton, gedit_status_menu_button, GTK_TYPE_MENU_BUTTON,
                         g_type_add_class_private (g_define_type_id, sizeof (GeditStatusMenuButtonClassPrivate)))

static void
gedit_status_menu_button_finalize (GObject *object)
{
	G_OBJECT_CLASS (gedit_status_menu_button_parent_class)->finalize (object);
}

static void
gedit_status_menu_button_set_label (GeditStatusMenuButton *button,
				    const gchar         *label)
{
	gtk_label_set_markup (GTK_LABEL (button->priv->label), label);
}

static const gchar *
gedit_status_menu_button_get_label (GeditStatusMenuButton *button)
{
	return gtk_label_get_label (GTK_LABEL (button->priv->label));
}

static void
gedit_status_menu_button_get_property (GObject    *object,
				       guint       prop_id,
				       GValue     *value,
				       GParamSpec *pspec)
{
	GeditStatusMenuButton *obj = GEDIT_STATUS_MENU_BUTTON (object);

	switch (prop_id)
	{
		case PROP_LABEL:
			g_value_set_string (value, gedit_status_menu_button_get_label (obj));
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

static void
gedit_status_menu_button_set_property (GObject      *object,
				       guint         prop_id,
				       const GValue *value,
				       GParamSpec   *pspec)
{
	GeditStatusMenuButton *obj = GEDIT_STATUS_MENU_BUTTON (object);

	switch (prop_id)
	{
		case PROP_LABEL:
			gedit_status_menu_button_set_label (obj, g_value_get_string (value));
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

static void
gedit_status_menu_button_class_init (GeditStatusMenuButtonClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
	static const gchar style[] =
		"* {\n"
		  "-GtkButton-default-border : 0;\n"
		  "-GtkButton-default-outside-border : 0;\n"
		  "-GtkButton-inner-border: 0;\n"
		  "-GtkWidget-focus-line-width : 0;\n"
		  "-GtkWidget-focus-padding : 0;\n"
		  "padding: 1px 8px 2px 4px;\n"
		"}";

	object_class->finalize = gedit_status_menu_button_finalize;
	object_class->get_property = gedit_status_menu_button_get_property;
	object_class->set_property = gedit_status_menu_button_set_property;

	g_object_class_override_property (object_class, PROP_LABEL, "label");

	/* Bind class to template */
	gtk_widget_class_set_template_from_resource (widget_class,
	                                             "/org/gnome/gedit/ui/gedit-status-menu-button.ui");
	gtk_widget_class_bind_child (widget_class, GeditStatusMenuButtonPrivate, label);

	g_type_class_add_private (object_class, sizeof (GeditStatusMenuButtonPrivate));

	klass->priv = G_TYPE_CLASS_GET_PRIVATE (klass, GEDIT_TYPE_STATUS_MENU_BUTTON, GeditStatusMenuButtonClassPrivate);

	klass->priv->css = gtk_css_provider_new ();
	gtk_css_provider_load_from_data (klass->priv->css, style, -1, NULL);
}

static void
gedit_status_menu_button_init (GeditStatusMenuButton *self)
{
	GtkStyleContext *context;

	self->priv = G_TYPE_INSTANCE_GET_PRIVATE(self, GEDIT_TYPE_STATUS_MENU_BUTTON, GeditStatusMenuButtonPrivate);

	gtk_widget_init_template (GTK_WIDGET (self));

	/* make it as small as possible */
	context = gtk_widget_get_style_context (GTK_WIDGET (self));
	gtk_style_context_add_provider (context,
	                                GTK_STYLE_PROVIDER (GEDIT_STATUS_MENU_BUTTON_GET_CLASS (self)->priv->css),
	                                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

/**
 * gedit_status_menu_button_new:
 * @label: (allow-none):
 */
GtkWidget *
gedit_status_menu_button_new (void)
{
	return g_object_new (GEDIT_TYPE_STATUS_MENU_BUTTON, NULL);
}

/* ex:set ts=8 noet: */