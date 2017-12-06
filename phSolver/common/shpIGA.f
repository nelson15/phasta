      subroutine shpIGA(shp, shgl, C,shpIGA,shglIGA)

        include "common.h"
c
        dimension shp(nshl,ngauss), shgl(nsd,nshl,nguass)
     &            C(num_elem_1D, ipord+1,ipord+1),
     &            shpIGA(npro,nshl,ngauss),   shglIGA(npro,nsd,nshl,ngauss)
     &            xl(npro,nenl,nsd),

        real*8  Cm(nsd,npro,nshl)
        real*8  Cmg(nsd,npro,nshl),Cg2(nshl),Cg3(nshl)

        do i=1,npro
          do j=1,nsd
            Cm(j,i,:)=matmul(C(i,:,:),shp(:,intp))
            Cmg(j,i,:)=matmul(C(i:,:),shgl(1,:,intp))
          enddo
        enddo
       call Asbshp(Cm,shpIGA)
       call Asbshg(Cmg,Cm,shglIGA)
      return
      end
c remember to edit stuff
