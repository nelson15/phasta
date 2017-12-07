      subroutine shpIGA(shp, shgl, C,shpIGA,shglIGA,xl)

        include "common.h"
c
        dimension shp(nshl1D,ngauss1D), shgl(1,nshl1D,nguass1D)
     &            C(num_elem_1D, ipord+1,ipord+1),
     &            shpIGA(nshl,ngauss),   shglIGA(nsd,nshl,ngauss)
     &            xl(npro,nenl,nsd),

        real*8  Bez(num_elem_1D, ipord+1,nguass1D)
        real*8  Bezg(num_elem_1D, ipord+1,nguass1D)

        do i=1,ngauss1D
          do j=1,nsd1D
            Bez(i,:,j)=matmul(C(i,:,:),shp(:,j))
            Bezg(j,i,:)=matmul(C(i,:,:),shgl(1,:,j))
          enddo
        enddo
       call Asbshp(Bez,shpIGA)
       call Asbshg(Bezg,Bez,shglIGA)
      return
      end
