# For Custom Board l5-task2 from scratch

board_runner_args(jlink "--device=MCXA156")
board_runner_args(linkserver "--device=MCXA156:FRDM-MCXA156")
board_runner_args(pyocd "--target=mcxA156")

include(${ZEPHYR_BASE}/boards/common/linkserver.board.cmake) #default runner
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)      #another useful runner