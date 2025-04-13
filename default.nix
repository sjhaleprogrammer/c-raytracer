{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [ 
    # Core libraries
    pkgs.glfw 
    pkgs.vulkan-headers
    pkgs.vulkan-loader
    pkgs.vulkan-tools
    
    # Compiler and tools
    pkgs.gcc
    pkgs.pkg-config
  ];

  shellHook = ''  
    export VK_ICD_FILENAMES=${pkgs.mesa}/share/vulkan/icd.d/intel_icd.x86_64.json:${pkgs.mesa}/share/vulkan/icd.d/radeon_icd.x86_64.json
  '';
}