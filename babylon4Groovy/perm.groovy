@Grab(group='org.codehaus.gpars', module='gpars', version='1.2.1')

import groovyx.gpars.GParsPool

GParsPool.withPool {
   final List result = (1 .. 9).permutations().findAllParallel { x ->
      int ci = x[2]*x[8]
      x[0]*ci+13*x[1]*x[8]+x[3]*ci+12*x[4]*ci-x[5]*ci-11*ci+x[6]*x[7]*x[2]-10*ci == 66*ci 
   }

   println(result.size())
}

