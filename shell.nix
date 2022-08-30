{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
      # nativeBuildInputs is usually what you want -- tools you need to run
      nativeBuildInputs = with pkgs; [ gcc libpng libjpeg xorg.libX11 pkg-config freetype xorg.libXext python3 imagemagick python310Packages.lz4 python310Packages.pypng python310Packages.pypng gcc-arm-embedded];
  }
