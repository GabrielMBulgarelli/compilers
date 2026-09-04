CC := gcc
CSTD := -std=c17
WARNINGS := -Wall -Wextra -Wpedantic
ASMFLAGS := $(CSTD) -S -masm=intel

PROGRAMS := folding propagation const_propagation
ASM_FILES := $(foreach program,$(PROGRAMS),$(foreach level,0 1 2,asm/$(program)_O$(level).s))
IMAGES := images/environment.png \
	images/folding_O0.png images/folding_O2.png \
	images/propagation_O0.png images/propagation_O2.png \
	images/const_propagation_O0.png images/const_propagation_O2.png
PACKAGE := ../tareacorta1.tgz
PACKAGE_ROOT := tareacorta1
PACKAGE_FILES := report.tex metadata.tex report.pdf images src asm Makefile README.md

.PHONY: all assembly report clean package

all: assembly report

assembly: $(ASM_FILES)
	@for source in $(addprefix src/,$(addsuffix .c,$(PROGRAMS))); do \
		$(CC) $(CSTD) $(WARNINGS) -fsyntax-only "$$source"; \
	done

asm/%_O0.s: src/%.c
	@mkdir -p asm
	$(CC) $(ASMFLAGS) -O0 $< -o $@

asm/%_O1.s: src/%.c
	@mkdir -p asm
	$(CC) $(ASMFLAGS) -O1 $< -o $@

asm/%_O2.s: src/%.c
	@mkdir -p asm
	$(CC) $(ASMFLAGS) -O2 $< -o $@

report: assembly report.pdf

report.pdf: report.tex metadata.tex $(ASM_FILES) $(IMAGES)
	latexmk -pdf -interaction=nonstopmode -halt-on-error report.tex

package: all
	@tmp=$$(mktemp -d); \
	trap 'rm -R -- "$$tmp"' EXIT HUP INT TERM; \
	mkdir -p "$$tmp/stage/$(PACKAGE_ROOT)" "$$tmp/verify"; \
	cp -R $(PACKAGE_FILES) "$$tmp/stage/$(PACKAGE_ROOT)/"; \
	tar -czf $(PACKAGE) -C "$$tmp/stage" $(PACKAGE_ROOT); \
	test "$$(tar -tzf $(PACKAGE) | sed 's,/.*,,' | sort -u)" = $(PACKAGE_ROOT); \
	tar -xzf $(PACKAGE) -C "$$tmp/verify"; \
	$(MAKE) --no-print-directory -C "$$tmp/verify/$(PACKAGE_ROOT)" clean all

clean:
	rm -f $(ASM_FILES) report.pdf report.aux report.fdb_latexmk \
		report.fls report.log report.out report.toc
