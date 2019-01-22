import argparse
import glob
import json
import re

def _remove_degenerate_lines(doc, args):
	for i,fr in enumerate(doc['data']['sequence']['frames']):
		for j, line in enumerate(doc['data']['sequence']['frames'][i]['lines']):

			if len(line['points_x']) == 0:
				print("degenerate line.")
				#if not args.dry_run:
				del doc['data']['sequence']['frames'][i]['lines'][j]
	return doc

def _print_doc_info(doc):
	cts = []
	frames = doc['data']['sequence']['frames']
	for f in frames:
		nlines = len(f['lines'])
	cts.append(nlines)
	print("Document has %d frames." % len(frames))
	for c in cts:
		print(c)

def fix_wash_recursively(path, args):
	files = glob.glob("%s/*.wash"% path)
	for f in files:
		fix_wash(f, args)

def fix_wash(path, args):
	if args.verbose:
		print("Attempting to fix:" + path)

	with open(path) as f:
		data = f.read()

	doc = json.loads(data)

	_print_doc_info(doc)
	doc = _remove_degenerate_lines(doc, args)
	_print_doc_info(doc)
	#if args.dry_run:
	#	return

	dump = json.dumps(doc, indent=4)
	# dump = re.sub('\n +', lambda match: '\n' + '\t' * (len(match.group().strip('\n')) / 2), dump)
	with open(path, 'w') as f:
		f.write(dump)

if __name__ == "__main__":

	parser = argparse.ArgumentParser(description="fix one or multiple wash files for malformed meta and data")
	group = parser.add_mutually_exclusive_group()
	group.add_argument("-v", "--verbose", action="store_true")
	group.add_argument("-q", "--quiet", action="store_true")
	parser.add_argument("-d", "--dry_run", action="store_false")
	parser.add_argument("-b", "--batch", action="store_true")
	parser.add_argument("path", type=str, help="the file or path to operate on")
	# parser.add_argument("y", type=int, help="the exponent")
	args = parser.parse_args()
	if args.batch:
		fix_wash_recursively(args.path, args)
	else:
		fix_wash(args.path, args)

