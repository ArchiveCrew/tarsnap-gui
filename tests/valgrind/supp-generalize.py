#!/usr/bin/env python3

import sys
import subprocess

DEBUG = False

def process_chunk(chunk_pre):
    lines = chunk_pre.split("\n")

    # If the chunk is only a # line, bail
    if lines[0].startswith("# "):
        return chunk_pre

    # Strip { and } from the beginning / end
    if lines[0] == "{" and lines[-2] == "}" and lines[-1] == "":
        lines = lines[1:-2]
    else:
        raise Exception("Unexpected chunk beginning / end")

    # Strip lines that are not sufficiently general
    chunk_post = lines
    for i, line_unstripped in enumerate(lines):
        line = line_unstripped.strip()

        # Our functions all begin with "pl_", so omit those.
        if line.startswith("fun:") and "pl_" in line:
            chunk_post = lines[:i]
            break

    return "\n".join(["{"] + chunk_post + ["}"]) + "\n"


def chunkify(lines):
    chunks = []
    chunk = ""
    num_duplicates = 0
    for line in lines:
        chunk += line
        if line == "}\n" or line.startswith("# "):
            if chunk not in chunks:
                chunks.append(chunk)
            else:
                num_duplicates += 1
            chunk = ""
    if chunk:
        raise Exception("Incomplete chunk at end of files.")
    if DEBUG and num_duplicates > 0:
        print("\t\tEliminated %i duplicate chunks in pre" % num_duplicates)
    return chunks


def get_trimmed(chunk_pre, chunk_post):
    if len(chunk_pre) == len(chunk_post):
        return ""
    pre = chunk_pre.split("\n")
    post = chunk_post.split("\n")
    delta_num = len(pre) - len(post) + 2
    trimmed = "\n".join(pre[-delta_num:])
    return trimmed


def debug_trimmed(chunk_pre, chunk_post, out_debug):
    if len(chunk_pre) == len(chunk_post):
        out_debug.write(chunk_post)
        return
    trimmed = get_trimmed(chunk_pre, chunk_post)

    num_final_brace_newlines = 3
    out_debug.write(chunk_post[:-num_final_brace_newlines] + "\n")
    out_debug.write("        ----snip----" + "\n")
    out_debug.write(trimmed)


def process_chunks(chunks_pre, debug_filename):
    if DEBUG:
        out_debug = open(debug_filename, "at")

    chunks_post = []
    num_duplicates = 0
    for i, chunk_pre in enumerate(chunks_pre):
        chunk_post = process_chunk(chunk_pre)
        if chunk_post not in chunks_post:
            chunks_post.append(chunk_post)
        else:
            num_duplicates += 1
        if DEBUG:
            debug_trimmed(chunk_pre, chunk_post, out_debug)

    if DEBUG and num_duplicates > 0:
        print("\t\tEliminated %i duplicate chunks in post" % num_duplicates)

    if DEBUG:
        out_debug.close()
        if len(chunks_post) > len(set(chunks_post)):
            raise Exception("Still have some duplicate chunks!")

    return chunks_post


def main(infilename, outfilename):
    # Read file and split into chunks of lines delimited by # or }
    lines = open(infilename).readlines()
    chunks_pre = chunkify(lines)

    # Trim chunks
    chunks_post = process_chunks(chunks_pre, outfilename + ".debug")

    # Append to output file
    with open(outfilename, "at") as fp:
        for chunk in chunks_post:
            fp.write(chunk)


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
