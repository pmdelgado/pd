#include "m_pd.h"
#include <math.h>
#define LOGTEN 2.302585092994


/* ------------- Data space ----------------------- */

typedef struct _counter
{
  t_object x_obj;
  t_int i_count; //stores counter value
  t_float step;
  t_int i_down, i_up;
  t_outlet *f_out, *b_out;
} t_counter;



/*------------Constructor and declaration -----------------*/

static t_class *counter_class; // pointer to new class

/* Constructor */

static void *counter_new(t_floatarg f)
{
  t_counter *x = (t_counter *)pd_new(counter_class); // needs to return a pointer to the data space
  x->i_count = f; //assigns input to internal variable in dataspace t_counter
  outlet_new(&x->x_obj, &s_float); // constructs outlet of type float first argument - pointer to object, second argument - type
  return (void *)x;
}

/* ------------- Methods ----------------------- */
/* 

_float whenever a float is received by the object, added with class_addfloat in setup
_bang called when a bang is received, added with class_addbang in setup
_rats or whatever, added with class_addmethod in setup (class extension)

each method then has to be added in the class setup
*/

static void counter_bang(t_counter *x)
{
  post("Hey!");
  t_float f = x->i_count; // cast to float because outlet_float expects that
  x->i_count++;
  outlet_float(x->x_obj.ob_outlet, f);
}

static void counter_reset(t_counter *x)
{

}



/*------------ Class setup ----------*/

void counter_setup(void)
{
    //t_symbol *s = gensym("acoustics.pd");
    
    /* Generation of new class */    

  counter_class = class_new(gensym("counter"), (t_newmethod)counter_new, 0,
			    sizeof(t_counter), CLASS_DEFAULT, A_GIMME, 0); 
    /* instantiate object with constructor, destructor, size, A_GIMME means dynamic number of arguments to be passed at instantiation time */
    
    /*Add methods to class*/
  class_addmethod(counter_class, (t_method)counter_reset, gensym("reset"),0); // method for arbitrary selector
  class_addmethod(counter_class, (t_method)counter_set, gensym("set"),A_DEFFLOAT,0);
  class_addmethod(counter_class, (t_method)counter_reset, gensym("bound"),A_DEFFLOAT,A_DEFFLOAT,0);
  class_addbang(counter_class, counter_bang);
  //class_sethelpsymbol(mtof_class, s);  
}
