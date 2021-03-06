project(
  'gedit', 'c',
  version: '3.37.0',
  meson_version: '>= 0.53'
)

if host_machine.system() == 'darwin'
  add_languages('objc')
endif

gnome = import('gnome')
i18n = import('i18n')
pkg = import('pkgconfig')
python = import('python')

api_version = '3.38'

package_string = '@0@-@1@'.format(meson.project_name(), api_version)

# Paths
root_include_dir = include_directories('.')

srcdir = meson.current_source_dir()

bindir = join_paths(get_option('prefix'), get_option('bindir'))
libdir = join_paths(get_option('prefix'), get_option('libdir'))
libexecdir = join_paths(get_option('prefix'), get_option('libexecdir'))
datadir = join_paths(get_option('prefix'), get_option('datadir'))
pkgconfigdir = join_paths(libdir, 'pkgconfig')
pkglibdir = join_paths(libdir, meson.project_name())
pkgdatadir = join_paths(datadir, meson.project_name())
glibdir = join_paths(datadir, 'glib-2.0')

# Subprojects
if not get_option('buildtype').contains('plain')
  run_command('git', '-C', meson.source_root(), 'submodule', 'update', '--init', '--recursive')
endif

libgd_subproject = subproject(
  'libgd',
  default_options: [
    'with-tagged-entry=true',
    'static=true',
  ]
)

libgd_dep = libgd_subproject.get_variable('libgd_dep')

# Dependencies
gio_dep = dependency('gio-2.0', version: '>= 2.52')
gtk_dep = dependency('gtk+-3.0', version: '>= 3.22')
gtksourceview_dep = dependency('gtksourceview-4', version: '>= 4.0.2')
tepl_dep = dependency('tepl-4', version: '>= 4.5')
libpeas_gtk_dep = dependency('libpeas-gtk-1.0', version: '>= 1.14.1')
gspell_dep = dependency('gspell-1', version: '>= 1.0')

introspection_dep = dependency('gobject-introspection-1.0')
vapigen_dep = dependency('vapigen', version: '>= 0.25.1')

python3 = python.find_installation('python3')

build_checkupdate_plugin = host_machine.system() == 'windows'
if build_checkupdate_plugin
  libsoup_dep = dependency('libsoup-2.4', version: '>= 2.60')
endif

# Configurations
config_h = configuration_data()
config_h.set_quoted('PACKAGE_STRING', package_string)
config_h.set_quoted('GETTEXT_PACKAGE', meson.project_name())
config_h.set_quoted('LIBDIR', join_paths(get_option('prefix'), get_option('libdir')))
config_h.set_quoted('DATADIR', join_paths(get_option('prefix'), get_option('datadir')))
config_h.set_quoted('VERSION', meson.project_version())

version_array = meson.project_version().split('.')
config_h.set('GEDIT_MAJOR_VERSION', version_array[0])
config_h.set('GEDIT_MINOR_VERSION', version_array[1])
config_h.set('GEDIT_MICRO_VERSION', version_array[2])

configure_file(
  output: 'config.h',
  configuration: config_h
)

subdir('data')
subdir('po')
subdir('gedit')
subdir('plugins')

if get_option('gtk_doc')
  subdir('docs/reference')
endif

if get_option('user_documentation')
  subdir('help')
endif

meson.add_install_script(
  'build-aux/meson/post_install.py',
  get_option('prefix') / get_option('libdir'),
  get_option('prefix') / get_option('datadir')
)

summary('API version', api_version)
summary('Prefix', get_option('prefix'))
summary('API documentation', get_option('gtk_doc'))
summary('User documentation', get_option('user_documentation'))
summary('Require all tests', get_option('require_all_tests'))
