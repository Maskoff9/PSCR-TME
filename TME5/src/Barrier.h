#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr{
	class Barrier{
		public{
			void todo(int nbJob){
				for(int i=0;n<nbJob;i++){
					pool.submit(new MyJob(x,y,))
				}
			}
		}
	};


}



