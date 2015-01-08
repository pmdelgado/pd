#include "m_pd.h"
#include <math.h>
#define LOGTEN 2.302585092994

typedef struct prueba
{
  t_object x_ob;
} t_prueba;


/* Independent methods */

t_float prueba(t_float f)
{
    if (f <= -1500) return(0);
    else if (f > 1499) return(mtof(1499));
    else return (8.17579891564 * exp(.0577622650 * f));
}

/*------------Constructor and declaration -----------------*/

static t_class *prueba_class; // pointer to new class, where is the data space??

/* Constructor */

/*   _new is called when the object is created, added with class_new in setup */

static void *prueba_new(void)
{
  t_object *x = (t_object *)pd_new(prueba_class); // needs to return a pointer to the data space, in this case just t_object, otherwise t_prueba
  outlet_new(x, &s_float); // constructs outlet of type float
    return (x);
}

/* ------------- Data space ----------------------- */

/* Data space */

/* in this case data space is not needed because methods are used with a t_object directly, instead of declaring a typedef of t_prueba which contains a t_object */

/* ------------- Methods ----------------------- */
/* 

_float whenever a float is received by the object, added with class_addfloat in setup
_bang called when a bang is received, added with class_addbang in setup
_rats or whatever, added with class_addmethod in setup

each method then has to be added in the class setup
*/

static void prueba_float(t_object *x, t_float f) // what is the difference bw t_float and t_floatarg?
{
    outlet_float(x->ob_outlet, prueba(f));
}

static void prueba_bang(t_object *x) 
{
  post("Hello world!"); 
}


/*------------ Class setup ----------*/

void prueba_setup(void)
{
    //t_symbol *s = gensym("acoustics.pd");
    
    /* Generation of new class */    

    prueba_class = class_new(gensym("prueba"), prueba_new, 0,
			   sizeof(t_object), 0, 0); 
    /* instantiate object with constructor, destructor not necessary for default dataspace, here size of t_object is used, 
in order not to typedef a t_prueba with only a t_object member. */
    
    /*Add methods to class*/

    class_addfloat(prueba_class, (t_method)prueba_float); // add float method
    class_addbang(prueba_class, prueba_bang);
    //class_sethelpsymbol(mtof_class, s);  
}
