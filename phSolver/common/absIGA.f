       subroutine Asbshp(Cm,shpIGA)

       include "common.h"

      dimension Cm(nsd,npro,nshl)
     &          shpIGA(npro,nshl,ngauss)
       do i= 1:nshl
         shpIGA(i,intp)=C1(i)*C2(i)*C3(i)
      enddo

      subroutine Asbshgx(Cg1,C2,C3,shglIGA)

      include "common.h"

      dimension Cg1(nshl),C2(nshl),C3(nshl),
     &          shglIGA(nsd,nshl,ngauss)
      do i= 1:nshl
        shglIGA(1,i,intp)=Cg1(i)*C2(i)*C3(i)
      enddo


      subroutine Asbshgy(C1,Cg2,C3,shglIGA)

      include "common.h"

      dimension C1(nshl),Cg2(nshl),C3(nshl),
     &          shglIGA(nsd,nshl,ngauss)
      do i= 1:nshl
        shglIGA(2,i,intp)=C1(i)*Cg2(i)*C3(i)
      enddo


      subroutine Asbshgz(C1,C2,Cg3,shglIGA)

      include "common.h"

      dimension C1(nshl),C2(nshl),Cg3(nshl),
     &          shglIGA(nsd,nshl,ngauss)
      do i= 1:nshl
        shglIGA(3,i,intp)=C1(i)*C2(i)*Cg3(i)
      enddo
c check for npro decision and add in here
