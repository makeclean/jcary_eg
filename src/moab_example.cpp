#include <iostream>
#include <sstream>
#include <iomanip> // for setprecision
#include <limits> // for min/max values
#include <assert.h>
#include <math.h>
#include <time.h>
#include <vector>

#include "moab_example.hpp"

int main(int argc, char **argv) 
{
  // load the input file
  MBErrorCode result, rval;
  MBEntityHandle input_set;

  rval = MBI()->create_meshset( MESHSET_SET, input_set ); // create a meshset for data
  
  // build a fairly arbitary geometry
  MBEntityHandle handles[2];
  build_geometry(input_set,handles);

  MBTag density_tag;
  // create a tag
  std::cout << handles[0] << " " << handles[1] << std::endl;
  rval = MBI()->tag_get_handle( "Density",1, MB_TYPE_DOUBLE,density_tag,
				moab::MB_TAG_SPARSE|moab::MB_TAG_CREAT);
  if(rval != MB_SUCCESS)
    {
      std::cout << "Failed to create tag!" << std::endl;
      return rval;
    }
 
  double density = 9.0;
  double zero = 0.0;
  // tag the data
  rval = MBI()->tag_set_data( density_tag, &(handles[1]), 1, &density );
  rval = MBI()->tag_set_data( density_tag, &(handles[0]), 1, &zero );


  // save the mesh
  rval = MBI()->write_mesh("test.h5m");

  return 0;  
}

void build_geometry(MBEntityHandle input_set, MBEntityHandle surfs[2])
{
  MBErrorCode rval;
  // create 8 vertices
  MBEntityHandle eh;
  MBRange vertex_eh;
  double coords[3] = {-5.0,-5.0,-5.0};
  rval = MBI()->create_vertex(coords,eh);
  vertex_eh.insert(eh);
  coords[2] = 5.0;
  rval = MBI()->create_vertex(coords,eh);
  vertex_eh.insert(eh);
  coords[1] = 5.0;
  coords[2] = -5.0;
  rval = MBI()->create_vertex(coords,eh);
  vertex_eh.insert(eh);
  coords[2] = 5.0;
  rval = MBI()->create_vertex(coords,eh);
  vertex_eh.insert(eh);

  // add vertices to meshset
  rval = MBI()->add_entities(input_set,vertex_eh);

  // create some triangles
  MBEntityHandle tri_node[3];
  MBEntityHandle triangle;
  tri_node[0]=vertex_eh[0];tri_node[1]=vertex_eh[1];tri_node[2]=vertex_eh[2];
  rval = MBI()->create_element(MBTRI,tri_node,3,triangle);
  // add triangle to meshset
  rval = MBI()->add_entities(input_set,&triangle,1);
  surfs[0] = triangle;

  tri_node[0]=vertex_eh[1];tri_node[1]=vertex_eh[2];tri_node[2]=vertex_eh[3];
  rval = MBI()->create_element(MBTRI,tri_node,3,triangle);
  // add triangle to meshset
  rval = MBI()->add_entities(input_set,&triangle,1);
  surfs[1] = triangle;

  return;
}

MBInterface *MBI() 
{
    static MBCore instance;
    return &instance;
}
