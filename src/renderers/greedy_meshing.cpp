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
    ValRLpair(unsigned value, unsigned run_length, unsigned width, bool is_a_rectangle = false) : val(value), rl(run_length), wid(width),
    is_rect(is_a_rectangle) {};
    unsigned val = 0;
    unsigned rl = 0;
    unsigned wid = 0;
    bool is_rect = false;
};

int main()
{
    unsigned side_size = 5;

    /*std::vector<int> data = { 1, 1, 1, 2, 1, 1, 1, 1,
                              1, 1, 1, 1, 1, 1, 2, 2,
                              1, 1, 3, 3, 3, 2, 1, 2,
                              3, 3, 2, 1, 1, 0, 0, 0,
                              1, 1, 1, 2, 3, 3, 3, 0,
                              1, 1, 2, 2, 2, 3, 3, 3, 
                              0, 0, 0, 2, 2, 4, 4, 4,
                              0, 0, 2, 1, 1, 4, 4, 1 };*/
/* 
   std::vector<int> data = {  1, 1, 1, 1, 1, 1, 1, 1,
                              1, 1, 1, 1, 1, 1, 1, 1,
                              1, 1, 1, 1, 1, 1, 1, 1,
                              1, 1, 1, 2, 1, 1, 1, 1,
                              1, 1, 1, 2, 1, 1, 1, 1,
                              1, 1, 1, 1, 1, 1, 1, 1, 
                              1, 1, 1, 1, 1, 2, 1, 1,
                              1, 1, 1, 1, 1, 1, 1, 1 }; */

    std::vector<int> data = {0, 0, 1, 0, 0,
                             0, 0, 2, 2, 0,
                             0, 1, 1, 1, 0,
                             0, 1, 2, 1, 0,
                             0, 2, 1, 1, 0
                                    };

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


    //ValRLpair def;
    std::vector<ValRLpair> holder(64, {0,0});

    unsigned z = 0; 

    unsigned run_length = 0;
    unsigned prev_voxel_val =  data[0];
    unsigned x = 0;

    unsigned voxel_val = 0;
    unsigned index = 0;


    for (x = 1; x < side_size; x++)
    {
        index = xzToIndex(x,z,side_size);

        voxel_val = data[index];

        run_length++;

        if ( (voxel_val != prev_voxel_val))
        {   
            holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1, true};
            run_length = 0;
        }

        prev_voxel_val = voxel_val;
        


    }
    holder[xzToIndex( ((x-1)-run_length), z, side_size )] = {prev_voxel_val, (run_length+1), 1, true};

    std::cout << std::endl;
    unsigned width = 0;

    ValRLpair last_row_rectangle;
    ValRLpair previous_last_row_rectangle;
    unsigned negative_rl_counter =0;

    unsigned rl_to_reach;
    unsigned rl_counter;

    for (unsigned z = 1; z < side_size; z++)
    {   

        previous_last_row_rectangle = {0,0,0,false};
        run_length = 0;
        x = 0;
        rl_to_reach = 0;
        rl_counter  = 0;

        index = xzToIndex(x,z,side_size);
        voxel_val = data[index];
        //run_length++;


        last_row_rectangle = holder[xzToIndex(x, z-1, side_size)];

        if ( voxel_val == last_row_rectangle.val )
        {
            previous_last_row_rectangle = last_row_rectangle;
            previous_last_row_rectangle.wid++; 
            rl_counter = 0;      
        }
        else 
        {
            //previous_last_row_rectangle = {voxel_val, 1, 1, true};
        }

        prev_voxel_val = data[xzToIndex(0, z, side_size)];

        for (unsigned x = 1; x < side_size; x++)
        {
            index = xzToIndex(x,z,side_size);
            voxel_val = data[index];
            run_length++;
            rl_counter++;


            if (voxel_val == prev_voxel_val)
            {

                if ( (previous_last_row_rectangle.wid > 0) )//&& (rl_counter == previous_last_row_rectangle.rl))
                {
                    if (rl_counter == previous_last_row_rectangle.rl)
                    {
                        //WE HAVE A SET THAT MATCHES A PREVIOUS ROW RECTANGLE - place it in
                        holder[xzToIndex( (x-rl_counter), z, side_size )] = previous_last_row_rectangle;

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
                        rl_counter = 0;
                        run_length = 0;
                    }
                    else
                    {
                        //std::cout << "here" << std::endl;
                        //carry on...?
                    }
                    
                    
                }
                else if (voxel_val == holder[xzToIndex(x, z-1, side_size)].val)
                {
                    previous_last_row_rectangle = holder[xzToIndex(x, z-1, side_size)];
                    previous_last_row_rectangle.wid++;

                    holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1, true};
                    rl_counter = 0;
                    run_length = 0;
                } 
                else
                {
                    //holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1, true};
                    //rl_counter = 0;
                    //run_length = 0;
                }
                
            }
            else //(voxel_val != prev_voxel_val)
            {
                //holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1, true};
                //run_length = 0;

                if ( (previous_last_row_rectangle.wid > 0) )//&& (rl_counter == previous_last_row_rectangle.rl))
                {
                    if (rl_counter == previous_last_row_rectangle.rl)
                    {
                        //WE HAVE A SET THAT MATCHES A PREVIOUS ROW RECTANGLE - place it in
                        holder[xzToIndex( (x-rl_counter), z, side_size )] = previous_last_row_rectangle;

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
                        rl_counter = 0;
                        run_length = 0;
                    }
                    else
                    {
                        previous_last_row_rectangle = {0, 0, 0};
                        holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1, true};
                        rl_counter = 0;
                        run_length = 0;
                        //carry on...?
                    }
                    
                    
                }
                else if (voxel_val == holder[xzToIndex(x, z-1, side_size)].val)
                {
                    previous_last_row_rectangle = holder[xzToIndex(x, z-1, side_size)];
                    previous_last_row_rectangle.wid++;

                    holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1, true};
                    rl_counter = 0;
                    run_length = 0;
                }
                else
                {
                    holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1, true};
                    rl_counter = 0;
                    run_length = 0;
                }

            }
            



            
            
            
        

            prev_voxel_val = voxel_val;

    


           


        }

            run_length++;
            rl_counter++;
            x = side_size;
                if ( (previous_last_row_rectangle.wid > 0) )//&& (rl_counter == previous_last_row_rectangle.rl))
                {
                    if (rl_counter == previous_last_row_rectangle.rl)
                    {
                        //WE HAVE A SET THAT MATCHES A PREVIOUS ROW RECTANGLE - place it in
                        holder[xzToIndex( (x-rl_counter), z, side_size )] = previous_last_row_rectangle;

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
                        rl_counter = 0;
                        run_length = 0;
                    }
                    else
                    {
                        //carry on...?
                    }
                    
                    
                }
                else //if// (voxel_val == holder[xzToIndex(x, z-1, side_size)].val)
                {
                    //previous_last_row_rectangle = holder[xzToIndex(x, z-1, side_size)];
                    //previous_last_row_rectangle.wid++;

                    holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1, true};
                    rl_counter = 0;
                    run_length = 0;
                }
            


    }



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

}