# Makefile.am

AUTOMAKE_OPTIONS = foreign subdir-objects

# Build PAM module as a static library
lib_LIBRARIES = libpam_evo_common.a
libpam_evo_common_a_SOURCES = src/main.c
libpam_evo_common_a_CFLAGS = -I$(top_srcdir)/include
libpam_evo_common_a_LIBADD = vendor/libevopam.a

# Define build directory
builddir = $(top_builddir)/build

# Ensure the library is built in the build directory
all-local:
	@mkdir -p $(builddir)
	@cp libpam_evo_common.a $(builddir)/

# Clean build directory
clean-local:
	rm -rf $(builddir)

# Define where the binary and other files are installed
configdir = $(sysconfdir)/evosecurity
pamconfdir = $(sysconfdir)/pam.d

# Install hook to copy files as requested
install-data-hook:
	$(MKDIR_P) $(DESTDIR)$(configdir)
	$(MKDIR_P) $(pamconfdir)
	if [ ! -f $(DESTDIR)$(configdir)/config.ini ]; then \
		cp config/config.ini.default $(DESTDIR)$(configdir)/config.ini; \
	fi
	if [ ! -f $(pamconfdir)/evo_common ]; then \
		echo "auth sufficient pam_evo_common.so" > $(pamconfdir)/evo_common; \
	fi

# Handle installation of header files and other data
dist_noinst_HEADERS = include/evopam.h
