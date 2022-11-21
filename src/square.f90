program main
    implicit none

    include "mpif.h"

    integer ierr
    integer size
    integer rank
    
    integer*8 radius
    integer*8 square_of_radius
    integer*8 height

    integer*8 index
    integer*8 jndex

    integer*8 smaller_count
    integer*8 larger_count

    integer*8 smaller_count_global
    integer*8 larger_count_global

    integer*8 smaller_four_times
    integer*8 larger_four_times

    call MPI_INIT(ierr)
    call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierr)
    call MPI_COMM_SIZE(MPI_COMM_WORLD, size, ierr)

    if (rank == 0) then
        write (*, fmt = "(a)", advance = "no") "一辺の長さ(10のN乗)):"
        read *, radius
        radius = 10**radius
        square_of_radius = radius ** 2
        height = radius / size
    end if
    
    call MPI_Bcast(radius, 1, MPI_INTEGER8, 0, MPI_COMM_WORLD, ierr)
    call MPI_Bcast(square_of_radius, 1, MPI_INTEGER8, 0, MPI_COMM_WORLD, ierr)
    call MPI_Bcast(height, 1, MPI_INTEGER8, 0, MPI_COMM_WORLD, ierr)

    smaller_count = 0
    larger_count = 0

    do index = height * rank, height * (rank + 1) - 1
        do jndex = 0, radius - 1
            if (index**2 + jndex**2 <= square_of_radius) then
                larger_count = larger_count + 1
            else 
                exit
            end if
            if ((index + 1)** 2 + (jndex + 1)** 2 <= square_of_radius) then
                smaller_count = smaller_count + 1
            end if
        end do
    end do

    call MPI_REDUCE(smaller_count, smaller_count_global, 1, MPI_INTEGER8, MPI_SUM, 0, MPI_COMM_WORLD, ierr)
    call MPI_REDUCE(larger_count, larger_count_global, 1, MPI_INTEGER8, MPI_SUM, 0, MPI_COMM_WORLD, ierr)

    if (rank == 0) then
        smaller_four_times = 4 * smaller_count_global
        larger_four_times = 4 * larger_count_global

        print "('smaller_pi = 4 * ', i0, ' / ', i0)", smaller_count_global, square_of_radius
        print "(10X, ' = ', i0, '.', i0)", smaller_four_times / square_of_radius, mod(smaller_four_times, square_of_radius)

        print "(' larger_pi = 4 * ', i0, ' / ', i0)", larger_count_global, square_of_radius
        print "(10X, ' = ', i0, '.', i0)", larger_four_times / square_of_radius, mod(larger_four_times, square_of_radius)
    end if

    call MPI_FINALIZE(ierr)

end program main
