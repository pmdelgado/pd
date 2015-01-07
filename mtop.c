#include "m_pd.h"
#include <math.h>
#define LOGTEN 2.302585092994

t_float mtop(t_float f)
{
    if (f <= -1500) return(0);
    else if (f > 1499) return(mtof(1499));
    else return (8.17579891564 * exp(.0577622650 * f));
}

/* ------------- corresponding objects ----------------------- */

static t_class *mtop_class;

/* Constructor */

static void *mtop_new(void)
{
    t_object *x = (t_object *)pd_new(mtop_class);
    outlet_new(x, &s_float);
    return (x);
}

/* Define Float Outlet */

static void mtop_float(t_object *x, t_float f)
{
    outlet_float(x->ob_outlet, mtop(f));
}

/*------------ Class setup ----------*/

void mtop_setup(void)
{
    //t_symbol *s = gensym("acoustics.pd");
    mtop_class = class_new(gensym("mtop"), mtop_new, 0,
			   sizeof(t_object), 0, 0); // instantiate object with constructor
    class_addfloat(mtop_class, (t_method)mtop_float); // add float method
    //class_sethelpsymbol(mtof_class, s);  
}
