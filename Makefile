SUBDIRS = $(shell ls -d */)

makefile_contents = "\
TARGETS = \$$(patsubst %%.cpp,%%,\$$(wildcard *.cpp)) \
\nclean:\n\
\t@rm -rf *.dSYM\n \
\t@rm -rf \$$(TARGETS) \$$(foreach targ,\$$(TARGETS),\$$(targ).bin \$$(targ).out) \
"

.PHONY: all $(SUBDIRS)

all: $(SUBDIRS)

clean: $(SUBDIRS)

$(SUBDIRS):
	@printf $(makefile_contents) | sed -e 's/^ //' > $@Makefile
	cd $@ && make clean
	@rm -f $@Makefile
