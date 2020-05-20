import argparse
import os
from datetime import datetime
from time import sleep, time

from trains import Task


def main():
    print('TRAINS experiment monitor service\n')
    # Monitor settings
    parser = argparse.ArgumentParser(description='TRAINS monitor failing experiments')
    parser.add_argument('--project', type=str, default='all',
                        help='The name of the project to monitor, use \'all\' for all projects')
    parser.add_argument('--refresh-rate', type=float, default=10.,
                        help='Set refresh rate of the monitoring service, default every 10.0 sec')
    parser.add_argument('--kb-effect', type=int, default=2,
                        help='Set alert keyboard lighting effect type')
    parser.add_argument('--kb-color', type=str, default='#ff00c8',
                        help='Set alert LED color, use CSS RGB color scheme. Example: #000000 is black, '
                             'Default: #ff00c8 magenta rocks!')

    args = parser.parse_args()
    kb_color = args.kb_color
    try:
        args.kb_color = args.kb_color.replace('#', '')
        red = int(args.kb_color[0:2], 16)
        green = int(args.kb_color[2:4], 16)
        blue = int(args.kb_color[4:6], 16)
    except:
        print('Error: Could not parse "{}", expecting 3 bytes hex values. Example #1200ab'.format(kb_color))
        return

    if os.geteuid() != 0:
        print('Alert service must be run as root, otherwise it cannot access the keyboard USB drivers')
        print('please re-run with sudo')
        return

    print('Starting monitoring service\nProject: "{}"\nRefresh rate: {}s\nkeyboard settings: effect={} color={}\n'.format(
        args.project, args.refresh_rate, args.kb_effect, args.kb_color))

    timestamp = time()
    # main loop
    while True:
        previous_timestamp = timestamp
        timestamp = time()

        # retrieve experiments orders by last update time
        # filter out archived experiments and in development experiments (i.e. not executed by trains-agent)
        failed_tasks = Task.get_tasks(
            project_name=args.project if args.project.lower() != 'all' else None,
            task_filter={'status': ['failed'], 'order_by': ['-last_update'],
                         'page_size': 1, 'page': 0,
                         'status_changed': ['>{}'.format(datetime.utcfromtimestamp(previous_timestamp)), ],
                         'system_tags': ['-archived', '-development']})
        if failed_tasks:
            print('Experiment id={} failed, raising alert'.format(failed_tasks[0].id))
            # we have to first set the color in static effect (mode==1)
            # only then we can change to the requested effect mode
            os.system('{kbcmd} {effect} {red} {green} {blue}'.format(
                kbcmd=os.path.join(os.path.dirname(__file__), 'hv-kb390l-control', 'hv-kb390l-control'),
                effect=1, red=red, blue=blue, green=green))
            os.system('{kbcmd} {effect} {red} {green} {blue}'.format(
                kbcmd=os.path.join(os.path.dirname(__file__), 'hv-kb390l-control', 'hv-kb390l-control'),
                effect=args.kb_effect, red=red, blue=blue, green=green))
            print('')
        sleep(args.refresh_rate)


if __name__ == "__main__":
    main()
