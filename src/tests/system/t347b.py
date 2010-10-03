def _bar():
   """__NATIVE__
   PmReturn_t retval = PM_RET_OK;

   /* If wrong number of args, raise TypeError */
   if (NATIVE_GET_NUM_ARGS() != 0)
   {
       PM_RAISE(retval, PM_RET_EX_TYPE);
       return retval;
   }

   NATIVE_SET_TOS(PM_NONE);
   return retval;
   """
   pass

def bar():
   return _bar()
