{
  description = "one_at_a_time_please Qt application";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }: {
    packages.x86_64-linux.default = let
      pkgs = import nixpkgs { system = "x86_64-linux"; };
    in pkgs.stdenv.mkDerivation {
      pname = "one_at_a_time_please";
      version = "1.0.0";
      src = ./.;

      nativeBuildInputs = with pkgs; [
        qt6.qmake
        qt6.qtbase
        qt6.qttools
        qt6.wrapQtAppsHook
      ];

      buildInputs = with pkgs; [
        qt6.qtbase
      ];

      qmakeFlags = [ 
        "one_at_a_time_please.pro" 
        "QMAKE_CXXFLAGS+=-Wno-unused-variable"
      ];

      preBuild = ''
        mkdir -p i18n Languages
        
        # Run lrelease on your source translation files
        for ts in Languages/*.ts i18n/*.ts; do
          if [ -f "$ts" ]; then
            filename=$(basename "$ts" .ts)
            lrelease "$ts" -qm i18n/$filename.qm
            lrelease "$ts" -qm Languages/$filename.qm
          fi
        done
      '';
      installPhase = ''
        runHook preInstall
        mkdir -p $out/bin
        cp one_at_a_time_please $out/bin/
        runHook postInstall
      '';
    };

    devShells.x86_64-linux.default = let
      pkgs = import nixpkgs { system = "x86_64-linux"; };
    in pkgs.mkShell {
      inputsFrom = [ self.packages.x86_64-linux.default ];
    };
  };
}
