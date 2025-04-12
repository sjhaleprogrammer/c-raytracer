{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [ 
    #c libraries
    pkgs.glfw 
    pkgs.vulkan-volk
    pkgs.vulkan-headers
    pkgs.vulkan-loader 
    pkgs.libdecor
   
    

    #c compiler
    pkgs.gcc
   
    #tools
    pkgs.tree
    pkgs.pkg-config
 
  ];

  shellHook = ''
    export C_INCLUDE_PATH=${pkgs.vulkan-volk}/include:$C_INCLUDE_PATH
    export LIBRARY_PATH=${pkgs.vulkan-volk}/lib:$LIBRARY_PATH
  '';

  
}