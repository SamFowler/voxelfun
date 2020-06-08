#include "BlockMeshGenerator.h"

#include "../pch/pch_std.h"
//#include <iostream>

namespace BlockMeshGenerator
{

 

VertexArrayObject makeBlockVAO(const Block& block, const unsigned int& block_size, const MeshMethod& mesh_method)
{
    BlockMesh block_mesh;
    if (mesh_method == CULL_MESH_FAST) // doesn't check neighbouring blocks
        makeBlockMesh_Culling(block, block_size, block_mesh);
    else if (mesh_method == CULL_MESH_OPTIMAL) // checks neighbouring blocks for voxel visibility
        makeBlockMesh_Culling(block, block_size, block_mesh);
    else if (mesh_method == GREEDY_MESH)
        makeBlockMesh_Greedy(block, block_size ,block_mesh);
    else if (mesh_method == NAIVE_MESH)
        makeBlockMesh_Naive(block,block_size , block_mesh);
    else if (mesh_method == OPTIMAL_MESH)
        makeBlockMesh_Optimal(block, block_size, block_mesh);
    else 
        makeBlockMesh_Culling(block,block_size, block_mesh);

    return block_mesh.createBlockBuffer();
}

void makeBlockMesh_Naive  (const Block& block, const unsigned int& block_size, BlockMesh& block_mesh)
{

}

void makeBlockMesh_Culling(const Block& block, const unsigned int& block_size, BlockMesh& block_mesh)
{
    int element_count = 0;
    //int block_size = 8;
    for (unsigned int y = 0; y < block_size; y++)
    {
        for (unsigned int z = 0; z < block_size; z++)
        {
            for (unsigned int x = 0; x < block_size; x++)
            {
                VoxelPos voxel_pos = {x,y,z};
                
                unsigned int voxel_index = block.indexFromVoxelPos( voxel_pos );

                Voxel voxel = block.getVoxel( voxel_pos );

                Colour voxel_colour = block.getColour(voxel.getColourId());

                if (!voxel.hasXMinusNeighbour())
              		addFace(block_mesh, voxel, voxel_pos, voxel_colour, element_count, X_MINUS_FACE, X_MINUS_NORMAL_INDEX);
                if (!voxel.hasXPlusNeighbour())
              		addFace(block_mesh, voxel, voxel_pos, voxel_colour, element_count, X_PLUS_FACE, X_PLUS_NORMAL_INDEX);
                if (!voxel.hasYMinusNeighbour())
              		addFace(block_mesh, voxel, voxel_pos, voxel_colour, element_count, Y_MINUS_FACE, Y_MINUS_NORMAL_INDEX);
                if (!voxel.hasYPlusNeighbour())
              		addFace(block_mesh, voxel, voxel_pos, voxel_colour, element_count, Y_PLUS_FACE, Y_PLUS_NORMAL_INDEX);
                if (!voxel.hasZMinusNeighbour())
                	addFace(block_mesh, voxel, voxel_pos, voxel_colour, element_count, Z_MINUS_FACE, Z_MINUS_NORMAL_INDEX);
                if (!voxel.hasZPlusNeighbour())
                	addFace(block_mesh, voxel, voxel_pos, voxel_colour, element_count, Z_PLUS_FACE, Z_PLUS_NORMAL_INDEX);
            }
        }
    }

}

bool isFaceVisible(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& normal_index, const Block& block)
{


    if (normal_index == X_MINUS_NORMAL_INDEX) 
        return !block.getVoxel({layer, j, i}).hasXMinusNeighbour();
    else if (normal_index == X_PLUS_NORMAL_INDEX) 
        return !block.getVoxel({layer, j, i}).hasXPlusNeighbour();    
    else if (normal_index == Y_MINUS_NORMAL_INDEX) 
        return !block.getVoxel({i, layer, j}).hasYMinusNeighbour();
    else if (normal_index == Y_PLUS_NORMAL_INDEX) 
        return !block.getVoxel({i, layer, j}).hasYPlusNeighbour(); 
    else if (normal_index == Z_MINUS_NORMAL_INDEX) 
        return !block.getVoxel({i, j, layer}).hasZMinusNeighbour(); 
    else if (normal_index == Z_PLUS_NORMAL_INDEX) 
        return !block.getVoxel({i, j, layer}).hasZPlusNeighbour();
    else {
        std::cout << "[ERROR] Greedy meshing isFaceVisible bad return";
        return true;
    }
}


ColourID getVoxelColour(const unsigned& i, const unsigned& j, const unsigned& layer, const unsigned& normal_index, const Block& block, const unsigned& block_size, const unsigned& direction)
{
    if (isFaceVisible(i, j, layer, normal_index, block))
    {
        //return getVoxelColour(i, j, layer, block_size, direction, block);
        if (direction == 0)
            return block.getVoxelColourID({i, layer, j});
        else if (direction == 1)
            return block.getVoxelColourID({layer, j, i});
        else
            return block.getVoxelColourID({i, j, layer}); 
    }
    else
        return 0;
}


unsigned getLocalIndex(const unsigned& i, const unsigned& j, const unsigned& block_size)
{
    return (j * block_size) + i;
}

void meshRectangle(BlockMesh& mesh, const BlockMeshFace& rectangle, const Block& block, const unsigned& direction,const unsigned& layer,
                             const std::array<GLuint, 12>& face, unsigned& element_count, unsigned& normal_index)
{
    if (rectangle.colour == 0)
        return;

    unsigned x,y,z;



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


    Colour colour = block.getColour(rectangle.colour);

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

void processFirstGreedyColumn(const unsigned& i, const unsigned& j, unsigned& run_length, std::vector<BlockMeshFace>& mesh_faces, const ColourID& current_colour, 
                                const ColourID& previous_colour, const unsigned& block_size)
{
    run_length++;
                    
    if ( current_colour != previous_colour )
    {   
        mesh_faces[getLocalIndex( (i-run_length), j, block_size )] = {previous_colour, run_length, 1, (i-run_length), j};
        run_length = 0;
    }
}

void processFirstGreedyRow(const unsigned& i, const unsigned& j, const unsigned& layer, unsigned& run_length, BlockMeshFace& previous_rectangle, std::vector<BlockMeshFace>& mesh_faces, const ColourID& current_colour, 
                                const ColourID& previous_colour,  BlockMesh& block_mesh, const unsigned& block_size, const std::array<GLuint, 12>& face,
                                unsigned& element_count, const unsigned& direction, const Block& block, unsigned& normal_index)
{

    previous_rectangle = {0,0,0,0,0};
    run_length = 0;
            
    if ( current_colour == getVoxelColour(i, j-1, layer, normal_index, block, block_size, direction) )
    {
        previous_rectangle = mesh_faces[getLocalIndex(i, j-1, block_size)];
        previous_rectangle.run_width++; 
    }
    else
    {
        meshRectangle(block_mesh, mesh_faces[getLocalIndex(i, j-1, block_size)], block, direction, layer, face, element_count, normal_index);
    }



}

void processMainBody(const unsigned& i, const unsigned& j, const unsigned& layer, unsigned& run_length, BlockMeshFace& previous_rectangle, std::vector<BlockMeshFace>& mesh_faces, const ColourID& current_colour, 
                                const ColourID& previous_colour,  BlockMesh& block_mesh, const unsigned& block_size, const std::array<GLuint, 12>& face,
                                unsigned& element_count, const unsigned& direction, const Block& block, unsigned& normal_index)
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
            mesh_faces[getLocalIndex( (i-run_length), j, block_size)] = previous_rectangle;

            //mesh the rectangle


            // as the runlength of the rectangle from previous column has been reached, 
            // a new, different, rectangle must be at this row value in the previous column -
            if (current_colour == getVoxelColour(i, j-1, layer, normal_index, block, block_size, direction))
            {   // We fetch it if it is of the same voxel type
                previous_rectangle = mesh_faces[getLocalIndex(i, j-1, block_size)];
                previous_rectangle.run_width++; 
                
            }
            else 
            {   //else set rectangle to empty so we don't look to match to it
                previous_rectangle = {0, 0, 0, 0, 0};
                meshRectangle(block_mesh, mesh_faces[getLocalIndex(i, j-1, block_size)], block, direction, layer, face, element_count, normal_index);
            }

            run_length = 0;

        }

        // if rectangle runlength hasn't been reached and the voxel type has changed,
        // create a new rectangle for the runlength that was reached and set rectangle to empty so we don't look to match to it
        else if (current_colour != previous_colour)
        {
            mesh_faces[getLocalIndex( (i-run_length), j, block_size)] =  {previous_colour, run_length, 1, (i-run_length), j};
                                    
                                    
            if (current_colour == getVoxelColour(i, j-1, layer, normal_index, block, block_size, direction))
            {   // We fetch it if it is of the same voxel type
                previous_rectangle = mesh_faces[getLocalIndex(i, j-1, block_size)];

                if (previous_rectangle.colour > 0)
                {
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
                    meshRectangle(block_mesh, previous_rectangle, block, direction, layer, face, element_count, normal_index);
                else 
                    meshRectangle(block_mesh, mesh_faces[getLocalIndex(i, j-1, block_size)], block, direction, layer, face, element_count, normal_index);
                

                previous_rectangle = {0, 0, 0, 0, 0};

            }

            run_length = 0;
        }
        else
        {                       
            if (current_colour != getVoxelColour(i, j-1, layer, normal_index, block, block_size, direction))
            {
                meshRectangle(block_mesh, mesh_faces[getLocalIndex(i, j-1, block_size)], block, direction, layer, face, element_count, normal_index);
            }
        }
        
        
    }

    // else if we are not trying to match to rectangle from previous column,
    // get the rectangle from the previous column and check if the voxels match with this voxel
                            
    else if (current_colour == mesh_faces[getLocalIndex(i, j-1, block_size)].colour)
    {
        mesh_faces[getLocalIndex( (i-run_length), j, block_size )] = {previous_colour, run_length, 1, (i-run_length), j};

        previous_rectangle = mesh_faces[getLocalIndex(i, j-1, block_size)];
        previous_rectangle.run_width++;

        run_length = 0;
    } 
    // else if there are no rectangles to match to, create a new one for the previous run length
    else if (current_colour != previous_colour)
    {
        mesh_faces[getLocalIndex( (i-run_length), j, block_size )] = {previous_colour, run_length, 1, (i-run_length), j};

        run_length = 0;
                            
        if (current_colour != getVoxelColour(i, j-1, layer, normal_index, block, block_size, direction))
        {
            meshRectangle(block_mesh, mesh_faces[getLocalIndex(i, j-1, block_size)], block, direction, layer, face, element_count, normal_index);
        }
        
    }
    else
    {   
        meshRectangle(block_mesh, mesh_faces[getLocalIndex(i, j-1, block_size)], block, direction, layer, face, element_count, normal_index);

    }
        
}


void fillLastGreedyRow(const unsigned& i, const unsigned& j, const unsigned& layer, unsigned& run_length, BlockMeshFace& previous_rectangle, std::vector<BlockMeshFace>& mesh_faces, const ColourID& current_colour, 
                                const ColourID& previous_colour, const unsigned& block_size, const std::array<GLuint, 12>& face,
                                const unsigned& direction, const Block& block, unsigned& normal_index)
{
    run_length++;

    if ( (previous_rectangle.run_width > 0) )
    {
        if (run_length == previous_rectangle.run_length)
        {
            //WE HAVE A SET THAT MATCHES A PREVIOUS ROW RECTANGLE - place it in
            mesh_faces[getLocalIndex( (i-run_length), j, block_size )] = previous_rectangle;

            // as runlength of previous row has been reached, a new rectanlge must be there
                            
            if (current_colour == getVoxelColour(i, j-1, layer, normal_index, block, block_size, direction))
            {                   
                previous_rectangle = mesh_faces[getLocalIndex(i, j-1, block_size)];  
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
    
        mesh_faces[getLocalIndex( (i-run_length), j, block_size )] = {previous_colour, run_length, 1, (i-run_length), j};
        run_length = 0;
    }
}


void makeBlockMesh_Greedy (const Block& block, const unsigned int& block_size, BlockMesh& block_mesh)
{

    // TODO: this whole greedy meshing pipeline is disgustingly written and hard to follow through. needs major clean up

    unsigned direction = 0;
    unsigned layer = 0; 

    std::array<GLuint, 12> face_plus;
    std::array<GLuint, 12> face_minus;
    GLuint normal_index_plus;
    GLuint normal_index_minus;

    unsigned element_count = 0;


    for (direction = 0; direction < 3; direction++)
    {
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

        for (unsigned layer = 0; layer < block_size; layer++ )
        {

            if (direction == 0 && layer == block_size-3)
                std::cout << "";


            std::vector<BlockMeshFace> mesh_faces_plus(block_size*block_size, {0,0,0,0,0});
            std::vector<BlockMeshFace> mesh_faces_minus(block_size*block_size, {0,0,0,0,0});
            //Voxel temp;
            //const Voxel& current_voxel = temp;
            ColourID current_colour_plus;
            ColourID current_colour_minus;

            unsigned run_length_plus = 0;
            unsigned run_length_minus = 0;

            unsigned i = 0;
            unsigned j = 0;     



            ColourID previous_colour_plus = getVoxelColour(i, j, layer, normal_index_plus, block, block_size, direction);
            ColourID previous_colour_minus = getVoxelColour(i, j, layer, normal_index_minus, block, block_size, direction);
            

            /* ------------START FIRST i ROW----------- */
            //loop over first column only to initialise rectangle array
            for (i = 1; i < block_size; i++)
            {
                current_colour_plus = getVoxelColour(i, j, layer, normal_index_plus, block, block_size, direction);
                current_colour_minus = getVoxelColour(i, j, layer, normal_index_minus, block, block_size, direction);


                processFirstGreedyColumn(i, j, run_length_plus, mesh_faces_plus, current_colour_plus, previous_colour_plus, block_size);

                processFirstGreedyColumn(i, j, run_length_minus, mesh_faces_minus, current_colour_minus, previous_colour_minus, block_size);

                

                previous_colour_plus = current_colour_plus;
                previous_colour_minus = current_colour_minus;
            }

            //Put last rectangle from first column in rectangle holder
            mesh_faces_plus[getLocalIndex( ((i-1)-run_length_plus), j, block_size )] = {previous_colour_plus, (run_length_plus+1), 1, ((i-1)-run_length_plus), j};
            mesh_faces_minus[getLocalIndex( ((i-1)-run_length_minus), j, block_size )] = {previous_colour_minus, (run_length_minus+1), 1, ((i-1)-run_length_minus), j};
            /* ------------END FIRST j COLUMN----------- */


            BlockMeshFace previous_rectangle_plus;
            BlockMeshFace previous_rectangle_minus;
            /* ------------START j = 1 onwards LOOP----------- */
            for (unsigned j = 1; j < block_size; j++)
            {   

                i = 0;  
                current_colour_plus = getVoxelColour(i, j, layer, normal_index_plus, block, block_size, direction);
                current_colour_minus = getVoxelColour(i, j, layer, normal_index_minus, block, block_size, direction);

                // run x=0 separately before loop so we don't have extra if checks for it in each loop
                processFirstGreedyRow(i, j, layer, run_length_plus, previous_rectangle_plus, mesh_faces_plus, current_colour_plus, 
                                                previous_colour_plus, block_mesh, block_size, face_plus, element_count, direction, block, normal_index_plus);
                
                processFirstGreedyRow(i, j, layer, run_length_minus, previous_rectangle_minus, mesh_faces_minus, current_colour_minus, 
                                                previous_colour_minus, block_mesh, block_size, face_minus, element_count, direction, block, normal_index_minus);
    


                previous_colour_plus = getVoxelColour(0, j, layer, normal_index_plus, block, block_size, direction);
                previous_colour_minus = getVoxelColour(0, j, layer, normal_index_minus, block, block_size, direction);


                for (unsigned i = 1; i < block_size; i++)
                {
                    current_colour_plus = getVoxelColour(i, j, layer, normal_index_plus, block, block_size, direction);
                    current_colour_minus = getVoxelColour(i, j, layer, normal_index_minus, block, block_size, direction);
                    
                    processMainBody(i, j, layer, run_length_plus, previous_rectangle_plus, mesh_faces_plus, current_colour_plus, 
                                                previous_colour_plus, block_mesh, block_size, face_plus, element_count, direction, block, normal_index_plus);
                    
                    processMainBody(i, j, layer, run_length_minus, previous_rectangle_minus, mesh_faces_minus, current_colour_minus, 
                                                previous_colour_minus, block_mesh, block_size, face_minus, element_count, direction, block, normal_index_minus);
                    
                    previous_colour_plus = current_colour_plus;
                    previous_colour_minus = current_colour_minus;

                } 

                i = block_size;
                fillLastGreedyRow(i, j, layer, run_length_plus, previous_rectangle_plus, mesh_faces_plus, current_colour_plus, 
                                                previous_colour_plus, block_size, face_plus, direction, block, normal_index_plus);
                fillLastGreedyRow(i, j, layer, run_length_minus, previous_rectangle_minus, mesh_faces_minus, current_colour_minus, 
                                                previous_colour_minus, block_size, face_minus, direction, block, normal_index_minus);

            }

            j = block_size;
            for (unsigned i = 0; i < block_size; i++)
            {
                meshRectangle(block_mesh, mesh_faces_plus[getLocalIndex( i, j-1, block_size )], block, direction, layer, face_plus, element_count, normal_index_plus);
                meshRectangle(block_mesh, mesh_faces_minus[getLocalIndex( i, j-1, block_size )], block, direction, layer, face_minus, element_count, normal_index_minus);
            }

        }//end layer
    
    }//direction

}


void makeBlockMesh_Optimal(const Block& block, const unsigned int& block_size, BlockMesh& block_mesh)
{

}



void addFace(BlockMesh& mesh, const Voxel& voxel, const VoxelPos& voxel_pos, const Colour& voxel_colour,
                                 int& element_count, const std::array<GLuint, 12>& face_verts, const GLuint& normal_index)
{

        //TODO: make this pack bits into a few bytes rather than large number of bytes for each vertex attribute
        int index = 0;
        for (int i = 0; i < 4; i++)
        {
            mesh.vertices.push_back(face_verts[index++] + voxel_pos.x);
            mesh.vertices.push_back(face_verts[index++] + voxel_pos.y);
            mesh.vertices.push_back(face_verts[index++] + voxel_pos.z);

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