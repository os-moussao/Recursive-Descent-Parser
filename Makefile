all: parser

%: %.c
	cc $< -o $@.out

%.out: %.c
	cc $< -o $@

clean:
	rm -f *.out

# alias
cl: clean
