#include "ChunkMeshGenerator.h"

#include <iostream>

namespace ChunkMeshGenerator
{



VertexArrayObject makeChunkVAO(const Chunk& chunk, const unsigned int& chunk_size, const MeshMethod& mesh_method)
{
    ChunkMesh chunk_mesh;
    if (mesh_method == CULL_MESH_FAST) // doesn't check neighbouring chunks
        makeChunkMesh_Culling(chunk, chunk_size, chunk_mesh);
    else if (mesh_method == CULL_MESH_OPTIMAL) // checks neighbouring chunks for voxel visibility
        makeChunkMesh_Culling(chunk, chunk_size, chunk_mesh);
    else if (mesh_method == GREEDY_MESH)
        makeChunkMesh_Greedy(chunk, chunk_size ,chunk_mesh);
    else if (mesh_method == NAIVE_MESH)
        makeChunkMesh_Naive(chunk,chunk_size , chunk_mesh);
    else if (mesh_method == OPTIMAL_MESH)
        makeChunkMesh_Optimal(chunk, chunk_size, chunk_mesh);
    else 
        makeChunkMesh_Culling(chunk,chunk_size, chunk_mesh);

    return chunk_mesh.createChunkBuffer();
}

void makeChunkMesh_Naive  (const Chunk& chunk, const unsigned int& chunk_size, ChunkMesh& chunk_mesh)
{

}

void makeChunkMesh_Culling(const Chunk& chunk, const unsigned int& chunk_size, ChunkMesh& chunk_mesh)
{
    int element_count = 0;
    //int chunk_size = 8;
    for (unsigned int y = 0; y < chunk_size; y++)
    {
        for (unsigned int z = 0; z < chunk_size; z++)
        {
            for (unsigned int x = 0; x < chunk_size; x++)
            {
                VoxelInChunkPos voxel_pos = {x,y,z};
                
                unsigned int voxel_index = chunk.indexFromInChunkPos( voxel_pos );

                Voxel voxel = chunk.getVoxel( voxel_pos );

                Colour voxel_colour = chunk.getColour(voxel.getColourId());

                if (!voxel.hasXMinusNeighbour())
              		addFace(chunk_mesh, voxel, voxel_pos, voxel_colour, element_count, X_MINUS_FACE, X_MINUS_NORMAL_INDEX);
                if (!voxel.hasXPlusNeighbour())
              		addFace(chunk_mesh, voxel, voxel_pos, voxel_colour, element_count, X_PLUS_FACE, X_PLUS_NORMAL_INDEX);
                if (!voxel.hasYMinusNeighbour())
              		addFace(chunk_mesh, voxel, voxel_pos, voxel_colour, element_count, Y_MINUS_FACE, Y_MINUS_NORMAL_INDEX);
                if (!voxel.hasYPlusNeighbour())
              		addFace(chunk_mesh, voxel, voxel_pos, voxel_colour, element_count, Y_PLUS_FACE, Y_PLUS_NORMAL_INDEX);
                if (!voxel.hasZMinusNeighbour())
                	addFace(chunk_mesh, voxel, voxel_pos, voxel_colour, element_count, Z_MINUS_FACE, Z_MINUS_NORMAL_INDEX);
                if (!voxel.hasZPlusNeighbour())
                	addFace(chunk_mesh, voxel, voxel_pos, voxel_colour, element_count, Z_PLUS_FACE, Z_PLUS_NORMAL_INDEX);
            }
        }
    }

}
/*
const Voxel& getChunkVoxel(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& chunk_size, const unsigned& direction, const Chunk& chunk)
{
    if (direction == 0)
        return chunk.getVoxel({i, layer, j});
    else if (direction == 1)
        return chunk.getVoxel({layer, j, i});
    else
        return chunk.getVoxel({i, j, layer});

}*/

ColourID getVoxelColour(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& chunk_size, const unsigned& direction, const Chunk& chunk)
{
    if (direction == 0)
        return chunk.getVoxelColourID({i, layer, j});
    else if (direction == 1)
        return chunk.getVoxelColourID({layer, j, i});
    else
        return chunk.getVoxelColourID({i, j, layer}); 
}

bool isFaceVisible(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& normal_index, const Chunk& chunk)
{


    if (normal_index == X_MINUS_NORMAL_INDEX) 
        return !chunk.getVoxel({layer, j, i}).hasXMinusNeighbour();
    else if (normal_index == X_PLUS_NORMAL_INDEX) 
        return !chunk.getVoxel({layer, j, i}).hasXPlusNeighbour();    
    else if (normal_index == Y_MINUS_NORMAL_INDEX) 
        return !chunk.getVoxel({i, layer, j}).hasYMinusNeighbour();
    else if (normal_index == Y_PLUS_NORMAL_INDEX) 
        return !chunk.getVoxel({i, layer, j}).hasYPlusNeighbour(); 
    else if (normal_index == Z_MINUS_NORMAL_INDEX) 
        return !chunk.getVoxel({i, j, layer}).hasZMinusNeighbour(); 
    else if (normal_index == Z_PLUS_NORMAL_INDEX) 
        return !chunk.getVoxel({i, j, layer}).hasZPlusNeighbour();
    else {
        std::cout << "[ERROR] Greedy meshing isFaceVisible bad return";
        return true;
    }
}

ColourID getVoxelColour(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& normal_index, const Chunk& chunk, const unsigned& chunk_size, const unsigned& direction)
{
    if (isFaceVisible(i, j, layer, normal_index, chunk))
        return getVoxelColour(i, j, layer, chunk_size, direction, chunk);
    else
        return 0;
}


unsigned getLocalIndex(const unsigned& i, const unsigned& j, const unsigned& chunk_size)
{
    return (j * chunk_size) + i;
}

void meshRectangle(ChunkMesh& mesh, const ChunkMeshFace& rectangle, const Chunk& chunk, const unsigned& direction,const unsigned& layer,
                             const std::array<GLuint, 12>& face, unsigned& element_count, unsigned& normal_index)
{
    if (rectangle.colour == 0)
        return;

    unsigned x,y,z;


    if (normal_index == X_MINUS_NORMAL_INDEX)
    {

    } 
    else if (normal_index == X_PLUS_NORMAL_INDEX)
    {

    }
    else if (normal_index == Y_MINUS_NORMAL_INDEX)
    {
        
    }
    else if (normal_index == Y_PLUS_NORMAL_INDEX)
    {
        
    }
    else if (normal_index == Z_MINUS_NORMAL_INDEX)
    {
        
    }
    else if (normal_index == Z_PLUS_NORMAL_INDEX)
    {
        
    }

    if (direction == 0)
    {
        x = rectangle.origin_i; 
        y = layer; 
        z = rectangle.origin_j;
        if (normal_index == Y_MINUS_NORMAL_INDEX)
        {
            mesh.vertices.push_back(face[0] + x );
            mesh.vertices.push_back(face[1] + y);
            mesh.vertices.push_back(face[2] + z  + rectangle.run_width-1 );

            mesh.vertices.push_back(face[3] + x);
            mesh.vertices.push_back(face[4] + y);
            mesh.vertices.push_back(face[5] + z);

            mesh.vertices.push_back(face[6] + x + rectangle.run_length-1 );
            mesh.vertices.push_back(face[7] + y);
            mesh.vertices.push_back(face[8] + z );

            mesh.vertices.push_back(face[9]  + x + rectangle.run_length-1 );
            mesh.vertices.push_back(face[10] + y);
            mesh.vertices.push_back(face[11] + z + rectangle.run_width-1);
        }
        else if (normal_index == Y_PLUS_NORMAL_INDEX)
        {
            mesh.vertices.push_back(face[0] + x + rectangle.run_length-1 );
            mesh.vertices.push_back(face[1] + y);
            mesh.vertices.push_back(face[2] + z );

            mesh.vertices.push_back(face[3] + x);
            mesh.vertices.push_back(face[4] + y);
            mesh.vertices.push_back(face[5] + z);

            mesh.vertices.push_back(face[6] + x );
            mesh.vertices.push_back(face[7] + y);
            mesh.vertices.push_back(face[8] + z + rectangle.run_width-1);

            mesh.vertices.push_back(face[9]  + x + rectangle.run_length-1 );
            mesh.vertices.push_back(face[10] + y);
            mesh.vertices.push_back(face[11] + z  + rectangle.run_width-1 );
        }
    }
    else if (direction == 1)
    {
        x = layer;
        y = rectangle.origin_j;
        z = rectangle.origin_i;

        if (normal_index == X_MINUS_NORMAL_INDEX)
        {
            mesh.vertices.push_back(face[0] + x );  
            mesh.vertices.push_back(face[1] + y );
            mesh.vertices.push_back(face[2] + z + rectangle.run_length-1 );

            mesh.vertices.push_back(face[3] + x );
            mesh.vertices.push_back(face[4] + y + rectangle.run_width-1 );
            mesh.vertices.push_back(face[5] + z + rectangle.run_length-1 );

            mesh.vertices.push_back(face[6] + x );
            mesh.vertices.push_back(face[7] + y + rectangle.run_width-1 );
            mesh.vertices.push_back(face[8] + z );

            mesh.vertices.push_back(face[9]  + x );
            mesh.vertices.push_back(face[10] + y  );
            mesh.vertices.push_back(face[11] + z );
        } 
        else if (normal_index == X_PLUS_NORMAL_INDEX)
        {

            mesh.vertices.push_back(face[0] + x );  
            mesh.vertices.push_back(face[1] + y );
            mesh.vertices.push_back(face[2] + z );

            mesh.vertices.push_back(face[3] + x );
            mesh.vertices.push_back(face[4] + y + rectangle.run_width-1 );
            mesh.vertices.push_back(face[5] + z );

            mesh.vertices.push_back(face[6] + x );
            mesh.vertices.push_back(face[7] + y + rectangle.run_width-1 );
            mesh.vertices.push_back(face[8] + z + rectangle.run_length-1 );

            mesh.vertices.push_back(face[9]  + x );
            mesh.vertices.push_back(face[10] + y  );
            mesh.vertices.push_back(face[11] + z + rectangle.run_length-1 );
        }
    }
    else if (direction == 2)
    {
        x = rectangle.origin_i;
        y = rectangle.origin_j;
        z = layer;

        if (normal_index == Z_MINUS_NORMAL_INDEX)
        {
            mesh.vertices.push_back(face[0] + x );
            mesh.vertices.push_back(face[1] + y  );
            mesh.vertices.push_back(face[2] + z );

            mesh.vertices.push_back(face[3] + x );
            mesh.vertices.push_back(face[4] + y + rectangle.run_width-1);
            mesh.vertices.push_back(face[5] + z );

            mesh.vertices.push_back(face[6] + x + rectangle.run_length-1);
            mesh.vertices.push_back(face[7] + y + rectangle.run_width-1);
            mesh.vertices.push_back(face[8] + z );

            mesh.vertices.push_back(face[9]  + x + rectangle.run_length-1 );
            mesh.vertices.push_back(face[10] + y );
            mesh.vertices.push_back(face[11] + z );
        }
        else if (normal_index == Z_PLUS_NORMAL_INDEX)
        {
            mesh.vertices.push_back(face[0] + x + rectangle.run_length-1);
            mesh.vertices.push_back(face[1] + y  + rectangle.run_width-1 );
            mesh.vertices.push_back(face[2] + z );

            mesh.vertices.push_back(face[3] + x );
            mesh.vertices.push_back(face[4] + y + rectangle.run_width-1);
            mesh.vertices.push_back(face[5] + z );

            mesh.vertices.push_back(face[6] + x );
            mesh.vertices.push_back(face[7] + y );
            mesh.vertices.push_back(face[8] + z );

            mesh.vertices.push_back(face[9]  + x + rectangle.run_length-1 );
            mesh.vertices.push_back(face[10] + y );
            mesh.vertices.push_back(face[11] + z );
        }
    }


    Colour colour = chunk.getColour(rectangle.colour);

    for (int k = 0; k < 4; k++)
    {
        mesh.colours.push_back(colour.r/255.0f);
        mesh.colours.push_back(colour.g/255.0f);
        mesh.colours.push_back(colour.b/255.0f);
        mesh.colours.push_back(colour.a/255.0f);

        mesh.normals.push_back(normal_index); 
    }


    mesh.elements.push_back(element_count);
    mesh.elements.push_back(element_count + 1);
    mesh.elements.push_back(element_count + 2);

    mesh.elements.push_back(element_count + 2);
    mesh.elements.push_back(element_count + 3);
    mesh.elements.push_back(element_count);
    element_count += 4; 

}

void processFirstGreedyColumn(const unsigned& i, const unsigned& j, unsigned& run_length, std::vector<ChunkMeshFace>& mesh_faces, const ColourID& current_colour, 
                                const ColourID& previous_colour, const unsigned& chunk_size)
{
    run_length++;
                    
    if ( current_colour != previous_colour )
    {   
        mesh_faces[getLocalIndex( (i-run_length), j, chunk_size )] = {previous_colour, run_length, 1, (i-run_length), j};
        run_length = 0;
    }
}

//processFirstGreedyRow(i, j, layer, run_length, previous_rectangle, mesh_faces, current_colour, previous_colour, chunk_mesh, chunk_size, face, element_count);
void processFirstGreedyRow(const unsigned& i, const unsigned& j, const unsigned& layer, unsigned& run_length, ChunkMeshFace& previous_rectangle, std::vector<ChunkMeshFace>& mesh_faces, const ColourID& current_colour, 
                                const ColourID& previous_colour,  ChunkMesh& chunk_mesh, const unsigned& chunk_size, const std::array<GLuint, 12>& face,
                                unsigned& element_count, const unsigned& direction, const Chunk& chunk, unsigned& normal_index)
{

    previous_rectangle = {0,0,0,0,0};
    run_length = 0;
            

    
    if ( current_colour == getVoxelColour(i, j-1, layer, chunk_size, direction, chunk) )
    {
        previous_rectangle = mesh_faces[getLocalIndex(i, j-1, chunk_size)];
        previous_rectangle.run_width++; 
    }
    else
    {
        meshRectangle(chunk_mesh, mesh_faces[getLocalIndex(i, j-1, chunk_size)], chunk, direction, layer, face, element_count, normal_index);
    }



}

void processMainBody(const unsigned& i, const unsigned& j, const unsigned& layer, unsigned& run_length, ChunkMeshFace& previous_rectangle, std::vector<ChunkMeshFace>& mesh_faces, const ColourID& current_colour, 
                                const ColourID& previous_colour,  ChunkMesh& chunk_mesh, const unsigned& chunk_size, const std::array<GLuint, 12>& face,
                                unsigned& element_count, const unsigned& direction, const Chunk& chunk, unsigned& normal_index)
{

    run_length++;

    // Check if we are currently trying to expand a rectangle from the previous column
    if ( (previous_rectangle.run_width > 0) ) 
    {   

        // if the voxels in this row have reached the same run length as the rectangle we are trying to expand,
        // we can add these voxels to that rectangle
        if (run_length == previous_rectangle.run_length) 
        {
            //We have a group of voxels that match the previous column rectangle - place them in
            mesh_faces[getLocalIndex( (i-run_length), j, chunk_size)] = previous_rectangle;
            //holder[xzToIndex( (x-run_length), z, side_size )] = previous_last_row_rectangle;

            //mesh the rectangle


            // as the runlength of the rectangle from previous column has been reached, 
            // a new, different, rectangle must be at this row value in the previous column -
            
            if (current_colour == getVoxelColour(i, j-1, layer, chunk_size, direction, chunk))
            {   // We fetch it if it is of the same voxel type
                previous_rectangle = mesh_faces[getLocalIndex(i, j-1, chunk_size)];
                previous_rectangle.run_width++; 
                
            }
            else 
            {   //else set rectangle to empty so we don't look to match to it
                previous_rectangle = {0, 0, 0, 0, 0};
                meshRectangle(chunk_mesh, mesh_faces[getLocalIndex(i, j-1, chunk_size)], chunk, direction, layer, face, element_count, normal_index);
            }

            run_length = 0;

        }

        // if rectangle runlength hasn't been reached and the voxel type has changed,
        // create a new rectangle for the runlength that was reached and set rectangle to empty so we don't look to match to it
        else if (current_colour != previous_colour)
        {
            mesh_faces[getLocalIndex( (i-run_length), j, chunk_size)] =  {previous_colour, run_length, 1, (i-run_length), j};
            //holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1, (x-run_length), z};
            
                
            if (current_colour == getVoxelColour(i, j-1, layer, chunk_size, direction, chunk))
            {   // We fetch it if it is of the same voxel type
                previous_rectangle = mesh_faces[getLocalIndex(i, j-1, chunk_size)];
                //previous_last_row_rectangle = holder[xzToIndex(x, z-1, side_size)];  

                if (previous_rectangle.colour > 0)
                {
                    //previous_last_row_rectangle = holder[xzToIndex(x, z-1, side_size)];  
                    previous_rectangle.run_width++; 
                }
                else
                {
                    previous_rectangle = {0, 0, 0, 0, 0};
                }
                
            }
            else 
            {   //else set rectangle to empty so we don't look to match to it
                previous_rectangle.run_width--;
                if (previous_rectangle.run_width > 0)
                    meshRectangle(chunk_mesh, previous_rectangle, chunk, direction, layer, face, element_count, normal_index);
                else 
                    meshRectangle(chunk_mesh, mesh_faces[getLocalIndex(i, j-1, chunk_size)], chunk, direction, layer, face, element_count, normal_index);
                

                previous_rectangle = {0, 0, 0, 0, 0};

            }

            run_length = 0;
        }
        else
        {                       
            if (current_colour != getVoxelColour(i, j-1, layer, chunk_size, direction, chunk))
            {
                meshRectangle(chunk_mesh, mesh_faces[getLocalIndex(i, j-1, chunk_size)], chunk, direction, layer, face, element_count, normal_index);
            }
        }
        
        
    }

    // else if we are not trying to match to rectangle from previous column,
    // get the rectangle from the previous column and check if the voxels match with this voxel
                            
    else if (current_colour == mesh_faces[getLocalIndex(i, j-1, chunk_size)].colour)
    {
        //holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1, (x-run_length), z};
        mesh_faces[getLocalIndex( (i-run_length), j, chunk_size )] = {previous_colour, run_length, 1, (i-run_length), j};

        previous_rectangle = mesh_faces[getLocalIndex(i, j-1, chunk_size)];
        previous_rectangle.run_width++;

        run_length = 0;
    } 
    // else if there are no rectangles to match to, create a new one for the previous run length
    else if (current_colour != previous_colour)
    {
        mesh_faces[getLocalIndex( (i-run_length), j, chunk_size )] = {previous_colour, run_length, 1, (i-run_length), j};
        //holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1, (x-run_length), z};
        run_length = 0;
                            
        if (current_colour != getVoxelColour(i, j-1, layer, chunk_size, direction, chunk))
        {
            meshRectangle(chunk_mesh, mesh_faces[getLocalIndex(i, j-1, chunk_size)], chunk, direction, layer, face, element_count, normal_index);
            //mesh_rect(holder[xzToIndex( x, z-1, side_size )]);
        }
        
    }
    else
    {   
        meshRectangle(chunk_mesh, mesh_faces[getLocalIndex(i, j-1, chunk_size)], chunk, direction, layer, face, element_count, normal_index);

    }
        
}


void fillLastGreedyRow(const unsigned& i, const unsigned& j, const unsigned& layer, unsigned& run_length, ChunkMeshFace& previous_rectangle, std::vector<ChunkMeshFace>& mesh_faces, const ColourID& current_colour, 
                                const ColourID& previous_colour, const unsigned& chunk_size, const std::array<GLuint, 12>& face,
                                const unsigned& direction, const Chunk& chunk)
{
    run_length++;

    if ( (previous_rectangle.run_width > 0) )
    {
        if (run_length == previous_rectangle.run_length)
        {
            //WE HAVE A SET THAT MATCHES A PREVIOUS ROW RECTANGLE - place it in
            mesh_faces[getLocalIndex( (i-run_length), j, chunk_size )] = previous_rectangle;
            //holder[xzToIndex( (x-run_length), z, side_size )] = previous_last_row_rectangle;

            // as runlength of previous row has been reached, a new rectanlge must be there
                            
            if (current_colour == getVoxelColour(i, j-1, layer, chunk_size, direction, chunk))
            {                   
                previous_rectangle = mesh_faces[getLocalIndex(i, j-1, chunk_size)];  
                previous_rectangle.run_width++; 
            }
            else 
            {
                previous_rectangle = {0, 0, 0, 0, 0};
            }
            run_length = 0;
        }
        else {/*carry on...?*/}
    }
    else 
    {
    
        mesh_faces[getLocalIndex( (i-run_length), j, chunk_size )] = {previous_colour, run_length, 1, (i-run_length), j};
        //holder[xzToIndex( (x-run_length), z, side_size )] = {prev_voxel_val, run_length, 1, (x-run_length), z};
        run_length = 0;
    }
}


void makeChunkMesh_Greedy (const Chunk& chunk, const unsigned int& chunk_size, ChunkMesh& chunk_mesh)
{
    unsigned direction = 0;
    unsigned layer = 0;

    std::array<GLuint, 12> face_plus;
    std::array<GLuint, 12> face_minus;
    GLuint normal_index_plus;
    GLuint normal_index_minus;

    unsigned element_count = 0;


    for (direction = 0; direction < 3; direction++)
    {
        GreedyProcessState plus_state(direction, chunk, chunk_size, true); // state for positive normal of direction
        GreedyProcessState minus_state(direction, chunk, chunk_size, false); //state for negative normal of direction

        if (direction == 0) 
        {
            face_plus = Y_PLUS_FACE;
            normal_index_plus = Y_PLUS_NORMAL_INDEX;
            face_minus = Y_MINUS_FACE;
            normal_index_minus = Y_MINUS_NORMAL_INDEX;
        }
        else if (direction == 1)
        {
            face_plus = X_PLUS_FACE;
            normal_index_plus = X_PLUS_NORMAL_INDEX;
            face_minus = X_MINUS_FACE;
            normal_index_minus = X_MINUS_NORMAL_INDEX;
        }
        else if (direction == 2)
        {
            face_plus = Z_PLUS_FACE;
            normal_index_plus = Z_PLUS_NORMAL_INDEX;
            face_minus = Z_MINUS_FACE;
            normal_index_minus = Z_MINUS_NORMAL_INDEX;
        }

        for (unsigned layer = 0; layer < chunk_size; layer++ )
        {

            std::vector<ChunkMeshFace> mesh_faces_plus(chunk_size*chunk_size*chunk_size, {0,0,0,0,0});
            std::vector<ChunkMeshFace> mesh_faces_minus(chunk_size*chunk_size*chunk_size, {0,0,0,0,0});
            //Voxel temp;
            //const Voxel& current_voxel = temp;
            ColourID current_colour_plus;
            ColourID current_colour_minus;

            unsigned run_length_plus = 0;
            unsigned run_length_minus = 0;

            unsigned i = 0;
            unsigned j = 0;     



            //const Voxel& previous_voxel = getChunkVoxel(i, j, layer, direction, chunk); //get first data element
            ColourID previous_colour_plus = getVoxelColour(i, j, layer, normal_index_plus, chunk, chunk_size, direction);
            ColourID previous_colour_minus = getVoxelColour(i, j, layer, normal_index_minus, chunk, chunk_size, direction);
            //previous_colour = getVoxelColour(i, j, layer, normal_index, chunk, chunk_size, direction);
            

            /* ------------START FIRST i COLUMN----------- */
            //loop over first column only to initialise rectangle array
            for (i = 1; i < chunk_size; i++)
            {
                //processFirstColumn(i, j, layer, normal_index, chunk, run_length, current_colour, previous_colour )
                current_colour_plus = getVoxelColour(i, j, layer, normal_index_plus, chunk, chunk_size, direction);
                current_colour_minus = getVoxelColour(i, j, layer, normal_index_minus, chunk, chunk_size, direction);


                processFirstGreedyColumn(i, j, run_length_plus, mesh_faces_plus, current_colour_plus, previous_colour_plus, chunk_size);

                processFirstGreedyColumn(i, j, run_length_minus, mesh_faces_minus, current_colour_minus, previous_colour_minus, chunk_size);

                

                previous_colour_plus = current_colour_plus;
                previous_colour_minus = current_colour_minus;
            }

            //Put last rectangle from first column in rectangle holder
            mesh_faces_plus[getLocalIndex( ((i-1)-run_length_plus), j, chunk_size )] = {previous_colour_plus, (run_length_plus+1), 1, ((i-1)-run_length_plus), j};
            mesh_faces_minus[getLocalIndex( ((i-1)-run_length_minus), j, chunk_size )] = {previous_colour_minus, (run_length_minus+1), 1, ((i-1)-run_length_minus), j};
            /* ------------END FIRST j COLUMN----------- */


            ChunkMeshFace previous_rectangle_plus;
            ChunkMeshFace previous_rectangle_minus;
            /* ------------START j = 1 onwards LOOP----------- */
            for (unsigned j = 1; j < chunk_size; j++)
            {   

                //current_colour = getVoxelColour(i, j, layer, normal_index, chunk, chunk_size, direction);
                i = 0;  
                current_colour_plus = getVoxelColour(i, j, layer, normal_index_plus, chunk, chunk_size, direction);
                current_colour_minus = getVoxelColour(i, j, layer, normal_index_minus, chunk, chunk_size, direction);

                // run x=0 separately before loop so we don't have extra if checks for it in each loop
                processFirstGreedyRow(i, j, layer, run_length_plus, previous_rectangle_plus, mesh_faces_plus, current_colour_plus, 
                                                previous_colour_plus, chunk_mesh, chunk_size, face_plus, element_count, direction, chunk, normal_index_plus);
                
                processFirstGreedyRow(i, j, layer, run_length_minus, previous_rectangle_minus, mesh_faces_minus, current_colour_minus, 
                                                previous_colour_minus, chunk_mesh, chunk_size, face_minus, element_count, direction, chunk, normal_index_minus);
    


                previous_colour_plus = getVoxelColour(0, j, layer, normal_index_plus, chunk, chunk_size, direction);
                previous_colour_minus = getVoxelColour(0, j, layer, normal_index_minus, chunk, chunk_size, direction);


                for (unsigned i = 1; i < chunk_size; i++)
                {
                    current_colour_plus = getVoxelColour(i, j, layer, normal_index_plus, chunk, chunk_size, direction);
                    current_colour_minus = getVoxelColour(i, j, layer, normal_index_minus, chunk, chunk_size, direction);
                    
                    processMainBody(i, j, layer, run_length_plus, previous_rectangle_plus, mesh_faces_plus, current_colour_plus, 
                                                previous_colour_plus, chunk_mesh, chunk_size, face_plus, element_count, direction, chunk, normal_index_plus);
                    
                    processMainBody(i, j, layer, run_length_minus, previous_rectangle_minus, mesh_faces_minus, current_colour_minus, 
                                                previous_colour_minus, chunk_mesh, chunk_size, face_minus, element_count, direction, chunk, normal_index_minus);
                    
                    previous_colour_plus = current_colour_plus;
                    previous_colour_minus = current_colour_minus;

                } 

                i = chunk_size;
                fillLastGreedyRow(i, j, layer, run_length_plus, previous_rectangle_plus, mesh_faces_plus, current_colour_plus, 
                                                previous_colour_plus, chunk_size, face_plus, direction, chunk);
                fillLastGreedyRow(i, j, layer, run_length_minus, previous_rectangle_minus, mesh_faces_minus, current_colour_minus, 
                                                previous_colour_minus, chunk_size, face_minus, direction, chunk);

            }

            j = chunk_size;
            for (unsigned i = 0; i < chunk_size; i++)
            {
                meshRectangle(chunk_mesh, mesh_faces_plus[getLocalIndex( i, j-1, chunk_size )], chunk, direction, layer, face_plus, element_count, normal_index_plus);
                meshRectangle(chunk_mesh, mesh_faces_minus[getLocalIndex( i, j-1, chunk_size )], chunk, direction, layer, face_minus, element_count, normal_index_minus);
            }

        }//end layer

    }//direction

}


void makeChunkMesh_Optimal(const Chunk& chunk, const unsigned int& chunk_size, ChunkMesh& chunk_mesh)
{

}



void addFace(ChunkMesh& mesh, const Voxel& voxel, const VoxelInChunkPos& voxel_pos, const Colour& voxel_colour,
                                 int& element_count, const std::array<GLuint, 12>& face_verts, const GLuint& normal_index)
{

        //TODO: make this pack bits into a few bytes rather than large number of bytes for each vertex attribute
        int index = 0;
        for (int i = 0; i < 4; i++)
        {
            mesh.vertices.push_back(face_verts[index++] + voxel_pos.pos.x);
            mesh.vertices.push_back(face_verts[index++] + voxel_pos.pos.y);
            mesh.vertices.push_back(face_verts[index++] + voxel_pos.pos.z);

            mesh.colours.push_back(voxel_colour.r/255.0f);
            mesh.colours.push_back(voxel_colour.g/255.0f);
            mesh.colours.push_back(voxel_colour.b/255.0f);
            mesh.colours.push_back(voxel_colour.a/255.0f);

            mesh.normals.push_back(normal_index);          
        }

        // add elements for two polygons representing the voxel face
        mesh.elements.push_back(element_count);
        mesh.elements.push_back(element_count + 1);
        mesh.elements.push_back(element_count + 2);

        mesh.elements.push_back(element_count + 2);
        mesh.elements.push_back(element_count + 3);
        mesh.elements.push_back(element_count);
        element_count += 4;

}


}