/* --------------------------------------------------------------------------
 *    Name: walk.c
 * Purpose: Associative array implemented as a trie
 * ----------------------------------------------------------------------- */

#include <stddef.h>

#include "base/errors.h"

#include "datastruct/trie.h"

#include "impl.h"

static error trie__walk_in_order(const trie__node_t *n,
                                 int                 level,
                                 trie_walk_callback *cb,
                                 void               *opaque)
{
  error err;

  if (n == NULL)
    return error_OK;

  err = trie__walk_in_order(n->child[0], level + 1, cb, opaque);
  if (!err)
  {
    if (IS_LEAF(n))
      err = cb(&n->item, level, opaque);
  }
  if (!err)
    err = trie__walk_in_order(n->child[1], level + 1, cb, opaque);

  return err;
}

error trie_walk(const trie_t       *t,
                trie_walk_callback *cb,
                void               *opaque)
{
  if (t == NULL)
    return error_OK;

  return trie__walk_in_order(t->root, 0, cb, opaque);
}
