#include "log.h"

#include <vector>

unsigned xzToIndex(unsigned x, unsigned z, unsigned side_size)
{
    return z * side_size + x;
}

struct ValRLpair
{   
    ValRLpair() : val(0), rl(0), wid(0) {};
    ValRLpair(unsigned value, unsigned run_length) : val(value), rl(run_length), wid(0) {};
    ValRLpair(unsigned value, unsigned run_length, unsigned width) : val(value), rl(run_length), wid(width) {};
    ValRLpair(unsigned value, unsigned run_length, unsigned width, unsigned x_, unsigned y_) 
        : val(value), rl(run_length), wid(width), x(x_), y(y_) {};
    unsigned val = 0;
    unsigned rl = 0;
    unsigned wid = 0;

    unsigned x = 0;
    unsigned y = 0;
};

int main()
{
    unsigned side_size = 8;

    std::vector<int> data = { 1, 1, 1, 2, 1, 1, 2, 1,
                              1, 1, 1, 1, 1, 1, 2, 2,
                              1, 1, 3, 3, 3, 2, 1, 2,
                              3, 3, 2, 1, 1, 0, 0, 0,
                              1, 1, 1, 2, 3, 3, 3, 0,
                              1, 1, 2, 2, 2, 3, 3, 3, 
                              0, 0, 0, 2, 2, 4, 4, 4,
                              0, 0, 2, 1, 1, 4, 4, 1 };

    /* std::vector<int> data(64);
    for (auto& it : data)
    {
        it = rand()%4;
    } */
/* 
   std::vector<int> data = {  1, 1, 1, 1, 1, 1, 1, 1,
                              1, 1, 1, 1, 1, 1, 1, 1,
                              1, 1, 1, 1, 1, 1, 1, 1,
                              1, 1, 1, 2, 1, 1, 1, 1,
                              1, 1, 1, 2, 1, 1, 1, 1,
                              1, 1, 1, 1, 1, 1, 1, 1, 
                              1, 1, 1, 1, 1, 2, 1, 1,
                              1, 1, 1, 1, 1, 1, 1, 1 }; */

  /*   std::vector<int> data = {0, 0, 1, 0, 0,
                             0, 0, 2, 2, 0,
                             0, 1, 1, 1, 0,
                             0, 1, 2, 1, 0,
                             0, 2, 1, 1, 0
                                    }; */

    /* ------------PRINTING----------- */
    {
        LOG(data.size());
        std::cout << std::endl;
        for (unsigned z = 0; z < side_size; z++)
        {   
            for (unsigned x = 0; x < side_size; x++)
            {
                unsigned index = xzToIndex(x,z,side_size);
                std::cout << data[index] << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        for (unsigned z = 0; z < side_size; z++)
        {   
            for (unsigned x = 0; x < side_size; x++)
            {
                unsigned index = xzToIndex(x,z,side_size);
                std::cout << "[" << x << "," << z << " (" << index;
                if (index < 10) {std::cout << " ";}
                std::cout << "): " << data[index] << "], ";
            }
            std::cout << std::endl;
        }
    }
    /* ------------END PRINTING----------- */

 
    std::vector<ValRLpair> holder(64, {0,0});

    unsigned voxel_val = 0;
    unsigned run_length = 0;

    unsigned x = 0;
    unsigned z = 0;     
    unsigned prev_voxel_val = data[xzToIndex(x,z, side_size)]; //get first data element

    /* ------------START FIRST Z COLUMN----------- */
    //loop over first column only to initialise rectangle array
    for (x = 1; x < side_size; x++)
    {
        voxel_val = data[xzToIndex(x,z,side_size)];
        run_length++;

        if ( voxel_val != prev_voxel_val )
        {   
            holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1};
            run_length = 0;
        }

        prev_voxel_val = voxel_val;
     }

    //Put last rectangle from first column in rectangle holder
    holder[xzToIndex( ((x-1)-run_length), z, side_size )] = {prev_voxel_val, (run_length+1), 1};
    /* ------------END FIRST Z COLUMN----------- */

    std::cout << std::endl;


    ValRLpair previous_last_row_rectangle;
    /* ------------START Z = 1 onwards LOOP----------- */
    for (unsigned z = 1; z < side_size; z++)
    {   

        previous_last_row_rectangle = {0,0,0};
        run_length = 0;
        x = 0;

        /* ------------START X = 0 ----------- */
        // run x=0 separately before loop so we don't have extra if checks for it in each loop
        voxel_val = data[xzToIndex(x,z,side_size)];

        if ( voxel_val == holder[xzToIndex(x, z-1, side_size)].val )
        {
            previous_last_row_rectangle = holder[xzToIndex(x, z-1, side_size)];
            previous_last_row_rectangle.wid++; 
        }

        prev_voxel_val = data[xzToIndex(0, z, side_size)];
        /* ------------END X = 0----------- */



        /* ------------START X = 1 onwards LOOP----------- */
        for (unsigned x = 1; x < side_size; x++)
        {
            voxel_val = data[xzToIndex(x,z,side_size)];
            run_length++;

            // Check if we are currently trying to expand a rectangle from the previous column
            if ( (previous_last_row_rectangle.wid > 0) ) 
            {   

                // if the voxels in this row have reached the same run length as the rectangle we are trying to expand,
                // we can add these voxels to that rectangle
                if (run_length == previous_last_row_rectangle.rl) 
                {
                    //We have a group of voxels that match the previous column rectangle - place them in
                    holder[xzToIndex( (x-run_length), z, side_size )] = previous_last_row_rectangle;

                    // as the runlength of the rectangle from previous column has been reached, 
                    // a new, different, rectangle must be at this row value in the previous column -
                    if (voxel_val == data[xzToIndex(x, z-1, side_size)])
                    {   // We fetch it if it is of the same voxel type
                        previous_last_row_rectangle = holder[xzToIndex(x, z-1, side_size)];  
                        previous_last_row_rectangle.wid++; 
                    }
                    else 
                    {   //else set rectangle to empty so we don't look to match to it
                        previous_last_row_rectangle = {0, 0, 0};
                    }

                    run_length = 0;

                }

                // if rectangle runlength hasn't been reached and the voxel type has changed,
                // create a new rectangle for the runlength that was reached and set rectangle to empty so we don't look to match to it
                else if (voxel_val != prev_voxel_val)
                {
                    holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1};
                    

                    //SEND previous_last_row_rectangle TO MESHER
                    previous_last_row_rectangle.wid--;



                    previous_last_row_rectangle = {0, 0, 0};
                    run_length = 0;
                }
            }

            // else if we are not trying to match to rectangle from previous column,
            // get the rectangle from the previous column and check if the voxels match with this voxel
            else if (voxel_val == holder[xzToIndex(x, z-1, side_size)].val)
            {
                previous_last_row_rectangle = holder[xzToIndex(x, z-1, side_size)];
                previous_last_row_rectangle.wid++;

                holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1};
                run_length = 0;
            } 
            // else if there are no rectangles to match to, create a new one for the previous run length
            else if (voxel_val != prev_voxel_val)
            {
                holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1};
                run_length = 0;
            }
             
            prev_voxel_val = voxel_val;

        } 
        /* ------------END X = 1 onwards LOOP----------- */



        /* ------------START X = SIDE_SIZE ----------- */
        // need special case for this as it needs to fill in the rectangle array before starting next z loop
        x = side_size;
        run_length++;

        if ( (previous_last_row_rectangle.wid > 0) )
        {
            if (run_length == previous_last_row_rectangle.rl)
            {
                //WE HAVE A SET THAT MATCHES A PREVIOUS ROW RECTANGLE - place it in
                holder[xzToIndex( (x-run_length), z, side_size )] = previous_last_row_rectangle;

                // as runlength of previous row has been reached, a new rectanlge must be there
                if (voxel_val == data[xzToIndex(x, z-1, side_size)])
                {
                    previous_last_row_rectangle = holder[xzToIndex(x, z-1, side_size)];  
                    previous_last_row_rectangle.wid++; 
                }
                else 
                {
                    previous_last_row_rectangle = {0, 0, 0};
                }
                run_length = 0;
            }
            else {/*carry on...?*/}
        }
        else 
        {
            holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1};
            run_length = 0;
        }
    }


    /* ------------PRINTING----------- */
    for (unsigned z = 0; z < side_size; z++)
    {
        for (unsigned x = 0; x < side_size; x++)
        {
            unsigned index = xzToIndex(x,z,side_size);

            //print layer
            std::cout << "["; if (index < 10) {std::cout << " ";}
            std::cout << index << ": " << holder[index].val << "," << holder[index].rl << "," << holder[index].wid << "], ";
        }
        std::cout << std::endl;
    }
    /* ------------END PRINTING----------- */

}