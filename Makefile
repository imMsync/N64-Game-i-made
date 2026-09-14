name: Build N64 ROM
on: [push, workflow_dispatch]

jobs:
  build:
    runs-on: ubuntu-latest
    container: ghcr.io/dragonminded/libdragon:latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Build ROM
        run: |
          git config --global --add safe.directory /__w/${{ github.event.repository.name }}/${{ github.event.repository.name }}
          libdragon make
