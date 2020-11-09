# Array of tests to run (in order)
# Each test contains
#   description - 
#   steps - A list of steps to perform, each step can have
#       inputs - A list of tuples for the inputs to apply at that step
#       *time - The time (in ms) to wait before continuing to the next step 
#           and before checking expected values for this step. The time should be a multiple of
#           the period of the system
#       *iterations - The number of clock ticks to wait (periods)
#       expected - The expected value at the end of this step (after the "time" has elapsed.) 
#           If this value is incorrect the test will fail early before completing.
#       * only one of these should be used
#   expected - The expected output (as a list of tuples) at the end of this test
# An example set of tests is shown below. It is important to note that these tests are not "unit tests" in 
# that they are not ran in isolation but in the order shown and the state of the device is not reset or 
# altered in between executions (unless preconditions are used).
tests = [ 
    {'description': 'First LED',
    'steps': [ {'inputs': [], 'time': 300 } ],
    'expected': [('PORTB',0x01)],
    },
    {'description': 'Second LED',
    'steps': [ {'inputs': [], 'time': 300 } ],
    'expected': [('PORTB',0x02)],
    },
    {'description': 'Third LED',
    'steps': [ {'inputs': [], 'time': 300 } ],
    'expected': [('PORTB',0x04)],
    },
    {'description': 'Second LED',
    'steps': [ {'inputs': [], 'time': 300 } ],
    'expected': [('PORTB',0x02)],
    },
    {'description': 'First LED',
    'steps': [ {'inputs': [], 'time': 300 } ],
    'expected': [('PORTB',0x01)],
    },
    {'description': 'Second LED',
    'steps': [ {'inputs': [], 'time': 300 } ],
    'expected': [('PORTB',0x02)],
    },
    {'description': 'Third LED',
    'steps': [ {'inputs': [], 'time': 300 } ],
    'expected': [('PORTB',0x04)],
    },
    {'description': 'Button press',
    'steps': [ {'inputs': [('PINA', 0x00)], 'time': 300 } ],
    'expected': [('PORTB',0x04)],
    },
    {'description': 'Button release',
    'steps': [ {'inputs': [('PINA', 0x01)], 'time': 300 } ],
    'expected': [('PORTB',0x04)],
    },
    {'description': 'Button press again',
    'steps': [ {'inputs': [('PINA', 0x00)], 'time': 300 } ],
    'expected': [('PORTB',0x01)],
    },
    {'description': 'Second LED',
    'steps': [ {'inputs': [('PINA', 0x00)], 'time': 300 } ],
    'expected': [('PORTB',0x02)],
    },
    # {'description': 'This test will run second.',
    # 'steps': [ {'inputs': [('PIN', <val>)],'iterations': 1}, # Set PIN to val then run one iteration
    #     {'inputs': [('PIN',<val>)], 'time': 300 }, # Set PIN to val then run 300 ms
    #     {'inputs': [('PIN',<val>)], 'iterations': 1, 'expected': [('PORT',<val>)]}, 
    #     {'inputs': [('PIN',<val>)], 'time': 600}, ],
    # 'expected': [('PORT',<val>)],
    # },
    ]

# Optionally you can add a set of "watch" variables these need to be global or static and may need
# to be scoped at the function level (for static variables) if there are naming conflicts. The 
# variables listed here will display everytime you hit (and stop at) a breakpoint
watch = ['Tick::out','PORTB', 'Tick::button']

