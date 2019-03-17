extern "C" {
#include "tsignal.h"
#include <malloc.h>
}

#include <lcm/lcm-cpp.hpp>
#include "Intersection.h"
#include "Movement.h"

int main(void) {
    Intersection *intersection = (Intersection*)malloc(sizeof(Intersection));
    while(1) {
        int result = get_sig_info("27.115.34.162", 9908, "YVF6R17413000163",10,297.03113,121.186967,31.276194, intersection);
    printf("\nmatch result is: %d",result);
    printf("\napproachId is: %s",intersection->approachId);
    printf("\nmovement is: %d",intersection->movement_num);
    for (int i = 0; i < intersection->movement_num; ++i) {
        printf("\nmovement id : %s",intersection->movements[i].movement_id);
        printf("\n\tstatus is : %d",intersection->movements[i].status);
        printf("\n\ttimeLeft is : %d",intersection->movements[i].timeLeft);
    }
    lcm::LCM lcm;
	 if(!lcm.good())
		return 1;
    }
	lcm.publish("SPAT_DATA", intersection);
	free(intersection);
}
