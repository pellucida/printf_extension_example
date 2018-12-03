/*
// @(#) widget.c - define a printf specfier that take a struct arg 
*/


# include	 <stdio.h>
# include	<stdlib.h>
# include	<printf.h>


//  register_printf_type () will used the next free slot >= PA_LAST
//  and return it;
// We use this global to pass it to arginfo function: print_widget_arginfo 

static	int	print_widget_user_type	= -1;

enum	{
	WDGT_NAME_SIZE	= 32,
};
struct wdgt_t {
	struct	{
		int	x;
		int	y;
	}	position;
  	char	name[WDGT_NAME_SIZE];
};
typedef	struct	wdgt_t	WIDGET;

// Registered by  register_printf_type()
// Copies struct pointed to by *ap to mem

void	widget_va_arg_function (void* mem, va_list* ap) {
	WIDGET	w	= va_arg(*ap, WIDGET);
	*(WIDGET*) mem	= w;
}


int	print_widget_arginfo (const struct printf_info* info, size_t n,
                      int* argtypes, int* size)
{
	if (n == 1) {
    		argtypes [0]	= print_widget_user_type;
    		size [0]	= sizeof (WIDGET);
	}
	return 1;
}

int	print_widget (
		FILE* stream,
		const struct printf_info* info,
		const void* const* args)
{
// Triple indirection. See glibc/stdio-common/tst-vfprintf-user-type.c
	WIDGET	w	= ***(WIDGET***)(args);

	char*	buffer	= 0;
	int	len	= asprintf (&buffer, "<Widget %s @(%d,%d)>",
				w.name, w.position.x, w.position.y);
	if (len != -1) {
		len = fprintf (stream, "%*s", (info->left ? -info->width : info->width), buffer);
		free (buffer);
	}
	return len;
}



int main (void) {
  
	WIDGET mywidget	= {.name = "mywidget",
			   .position	= {.x = 10, .y = 31}, };

	print_widget_user_type	= register_printf_type (widget_va_arg_function);
	register_printf_specifier ('W', print_widget, print_widget_arginfo);

  	printf ("|%W|\n", mywidget);
	printf ("|%55W|\n", mywidget);
	printf ("|%-55W|\n", mywidget);
	{ // Check that sprintf() works too :)
	char	buffer[1024];
	sprintf ( buffer, "|%-55W|\n", mywidget);
	fputs (buffer, stderr);
	}

	return 0;
}

