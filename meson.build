project( 'Hangman-GTK', 'cpp', version : '0.0.0', default_options : ['warning_level=3', 'cpp_std=c++17', 'werror=true', 'optimization=3'] )

python_exe = find_program( 'python3', 'python', required : true )

gtkdep = dependency( 'gtkmm-3.0' )

incdir = include_directories( 'includes' )
subdir( 'src' )

install_subdir( 'resources', install_dir : 'out' )

exe = executable( 'hangman', sources, dependencies : gtkdep, include_directories : incdir )