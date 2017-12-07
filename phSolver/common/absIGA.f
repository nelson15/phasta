       subroutine Asbshp(Bez,shpIGA)

       include "common.h"

      dimension Bez(num_elem_1D, ipord+1,nguass1D)
     &          shpIGA(nshl,ngauss)

      integer e((ipord+1)^3), n(ngauss^3)
      do i= 1:num_elem_1D
        do j= 1:num_elem_1D
          do k=1:num_elem_1D
            do ex=1:ipord+1
              do ey=1:ipord+1
                do ez=1:ipord+1
                  e=ex+(ey-1)*(ipord+1)+(ez-1)*(ipord+1)(ipord+1)
                  do intpx=1:ngauss1D
                    do intpy=1:ngauss1D
                      do intpz=1:ngauss1D
                        n=intpx+(intpy-1)*(ngauss1D)+(intpz-1)*(ngauss1D)(ngauss1D)
                        shpIGA(e,n)=Bez(i,ex,intpx)*Bez(j,ey,intpy)*
     &                              Bez(k,ez,intpz)
                      enddo
                    enddo
                  enddo
                enddo
              enddo
            enddo
          enddo
        enddo
      enddo
      return
      end

      subroutine Asbshg(Bezg,Bez,shglIGA)

      include "common.h"

      dimension Bez(num_elem_1D, ipord+1,nguass1D),
     &          Bezg(num_elem_1D, ipord+1,nguass1D)
     &          shglIGA(nsd,nshl,ngauss)
      integer e((ipord+1)^3), n(ngauss^3)
      do i= 1:num_elem_1D
        do j= 1:num_elem_1D
          do k=1:num_elem_1D
            do ex=1:ipord+1
             do ey=1:ipord+1
               do ez=1:ipord+1
                 e=ex+(ey-1)*(ipord+1)+(ez-1)*(ipord+1)(ipord+1)
                 do intpx=1:ngauss1D
                   do intpy=1:ngauss1D
                     do intpz=1:ngauss1D
                       n=intpx+(intpy-1)*(ngauss1D)+(intpz-1)*(ngauss1D)(ngauss1D)
                       shglIGA(1,e,n)=Bezg(i,ex,intpx)*Bez(j,ey,intpy)*
     &                                Bez(k,ez,intpz)
                       shglIGA(2,e,n)=Bez(i,ex,intpx)*Bezg(j,ey,intpy)*
     &                                Bez(k,ez,intpz)
                       shglIGA(3,e,n)=Bez(i,ex,intpx)*Bez(j,ey,intpy)*
     &                                Bezg(k,ez,intpz)
                     enddo
                   enddo
                 enddo
               enddo
             enddo
           enddo
         enddo
       enddo
      enddo
      return
      end
