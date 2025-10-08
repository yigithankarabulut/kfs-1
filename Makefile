IMAGE_NAME = norx:latest
CONTAINER_NAME = norx_container
BUILD_PLATFORM = linux/amd64

DOCKER = docker

all: build_kernel run_kernel

clean:
	@echo "--- Cleaning up build artifacts ---"
	@$(DOCKER) exec -t $(CONTAINER_NAME) make clean

fclean:
	@echo "--- Performing full cleanup inside container $(CONTAINER_NAME) ---"
	@$(DOCKER) exec -t $(CONTAINER_NAME) make fclean

build_container:
	@echo "--- Building Docker image for NorxOS ---"
	@echo "--- Building Docker image $(IMAGE_NAME) ---"
	@$(DOCKER) build --platform $(BUILD_PLATFORM) -t $(IMAGE_NAME) .

	@echo "--- Creating and starting new container $(CONTAINER_NAME) ---"
	@$(DOCKER) run -d \
		--name $(CONTAINER_NAME) \
		--rm \
		-it \
		-v $(CURDIR)/srcs:/srcs \
		$(IMAGE_NAME)

build_kernel:
	@echo "--- Building kernel in container $(CONTAINER_NAME) ---"
	@$(DOCKER) exec -t $(CONTAINER_NAME) make

run: run_kernel
run_kernel:
	@echo "--- Running kernel in container $(CONTAINER_NAME) ---"
	@qemu-system-i386 -cdrom srcs/norx.iso -vga std -display sdl

fclean_container: fclean
	@echo "--- Performing full cleanup: stopping container, removing container and image ---"
	-$(DOCKER) stop $(CONTAINER_NAME) > /dev/null 2>&1 || true
	-$(DOCKER) rm $(CONTAINER_NAME) > /dev/null 2>&1 || true
	-$(DOCKER) rmi $(IMAGE_NAME) > /dev/null 2>&1 || true
	@echo "Full cleanup complete."

.PHONY: all build clean fclean
