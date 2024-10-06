#ifndef _OVEN_SERVICE_H
#define  _OVEN_SERVICE_H

namespace oven
{
    class ovenservice 
    {
        public:

            ovenservice();

            ~ovenservice();

            
            static int32_t OVEN_fnReadOdorData();
            static int32_t OVEN_fnReadRadarData();

        protected:

        private:

           static int32_t OVEN_fnInit();
    }
}


#endif